#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int evType; int evTime; scalar_t__ evPtr; int /*<<< orphan*/  evPtrLength; int /*<<< orphan*/  evValue2; int /*<<< orphan*/  evValue; } ;
typedef  TYPE_1__ sysEvent_t ;
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_11__ {unsigned int maxsize; int /*<<< orphan*/  cursize; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ msg_t ;
typedef  int /*<<< orphan*/  evFrom ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  bufData ;
struct TYPE_13__ {int /*<<< orphan*/  value; } ;
struct TYPE_12__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_CharEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_JoystickEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CL_KeyEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CL_MouseEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CL_PacketEvent (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Cbuf_AddText (char*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ Com_GetEvent () ; 
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Com_RunAndTimeServerPacket (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int MAX_MSGLEN ; 
 int /*<<< orphan*/  MSG_Init (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ NET_GetLoopPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  NS_CLIENT ; 
 int /*<<< orphan*/  NS_SERVER ; 
 int /*<<< orphan*/  Q_random (int*) ; 
#define  SE_CHAR 134 
#define  SE_CONSOLE 133 
#define  SE_JOYSTICK_AXIS 132 
#define  SE_KEY 131 
#define  SE_MOUSE 130 
#define  SE_NONE 129 
#define  SE_PACKET 128 
 int /*<<< orphan*/  Z_Free (scalar_t__) ; 
 TYPE_4__* com_dropsim ; 
 TYPE_3__* com_sv_running ; 

int Com_EventLoop( void ) {
	sysEvent_t	ev;
	netadr_t	evFrom;
	byte		bufData[MAX_MSGLEN];
	msg_t		buf;

	MSG_Init( &buf, bufData, sizeof( bufData ) );

	while ( 1 ) {
		ev = Com_GetEvent();

		// if no more events are available
		if ( ev.evType == SE_NONE ) {
			// manually send packet events for the loopback channel
			while ( NET_GetLoopPacket( NS_CLIENT, &evFrom, &buf ) ) {
				CL_PacketEvent( evFrom, &buf );
			}

			while ( NET_GetLoopPacket( NS_SERVER, &evFrom, &buf ) ) {
				// if the server just shut down, flush the events
				if ( com_sv_running->integer ) {
					Com_RunAndTimeServerPacket( &evFrom, &buf );
				}
			}

			return ev.evTime;
		}


		switch ( ev.evType ) {
		default:
		  // bk001129 - was ev.evTime
			Com_Error( ERR_FATAL, "Com_EventLoop: bad event type %i", ev.evType );
			break;
        case SE_NONE:
            break;
		case SE_KEY:
			CL_KeyEvent( ev.evValue, ev.evValue2, ev.evTime );
			break;
		case SE_CHAR:
			CL_CharEvent( ev.evValue );
			break;
		case SE_MOUSE:
			CL_MouseEvent( ev.evValue, ev.evValue2, ev.evTime );
			break;
		case SE_JOYSTICK_AXIS:
			CL_JoystickEvent( ev.evValue, ev.evValue2, ev.evTime );
			break;
		case SE_CONSOLE:
			Cbuf_AddText( (char *)ev.evPtr );
			Cbuf_AddText( "\n" );
			break;
		case SE_PACKET:
			// this cvar allows simulation of connections that
			// drop a lot of packets.  Note that loopback connections
			// don't go through here at all.
			if ( com_dropsim->value > 0 ) {
				static int seed;

				if ( Q_random( &seed ) < com_dropsim->value ) {
					break;		// drop this packet
				}
			}

			evFrom = *(netadr_t *)ev.evPtr;
			buf.cursize = ev.evPtrLength - sizeof( evFrom );

			// we must copy the contents of the message out, because
			// the event buffers are only large enough to hold the
			// exact payload, but channel messages need to be large
			// enough to hold fragment reassembly
			if ( (unsigned)buf.cursize > buf.maxsize ) {
				Com_Printf("Com_EventLoop: oversize packet\n");
				continue;
			}
			Com_Memcpy( buf.data, (byte *)((netadr_t *)ev.evPtr + 1), buf.cursize );
			if ( com_sv_running->integer ) {
				Com_RunAndTimeServerPacket( &evFrom, &buf );
			} else {
				CL_PacketEvent( evFrom, &buf );
			}
			break;
		}

		// free any block data
		if ( ev.evPtr ) {
			Z_Free( ev.evPtr );
		}
	}

	return 0;	// never reached
}