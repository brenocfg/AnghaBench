#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct udp_pcb {int dummy; } ;
struct pbuf {int* payload; } ;
struct ip_addr {int dummy; } ;
struct TYPE_5__ {int type; scalar_t__ payload; } ;
struct TYPE_7__ {int /*<<< orphan*/  a; TYPE_1__ s; } ;
typedef  TYPE_3__ ledPacket_type ;
struct TYPE_6__ {int type; int param1; } ;
struct TYPE_8__ {TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_MODE_ACTIVE ; 
 int /*<<< orphan*/  BL_MODE_WAITING ; 
 int /*<<< orphan*/  DEBUGPIN_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGPIN_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Delay (int) ; 
 scalar_t__ LocalTime ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 int /*<<< orphan*/  PIN_High (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIN_Low (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PKT_TYPE_8BIT_CAL 139 
#define  PKT_TYPE_8BIT_RAW 138 
#define  PKT_TYPE_BL_INIT 137 
#define  PKT_TYPE_DOTCORRECT_PACK12 136 
#define  PKT_TYPE_DOTCORRECT_PACK6 135 
#define  PKT_TYPE_DOTCORRECT_PACK8 134 
#define  PKT_TYPE_FAN_CONFIG 133 
#define  PKT_TYPE_GET_LOOKUP 132 
#define  PKT_TYPE_GSVALS 131 
#define  PKT_TYPE_REBOOT 130 
#define  PKT_TYPE_RELAY_CTRL 129 
#define  PKT_TYPE_SET_LOOKUP 128 
 scalar_t__ POWER_ROW ; 
 int /*<<< orphan*/  PWR_CTRL_AC_0 ; 
 int /*<<< orphan*/  PWR_CTRL_AC_1 ; 
 int /*<<< orphan*/  UART_SendBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bootloaderMode ; 
 int /*<<< orphan*/  doLookupTableReadback () ; 
 int* fan_duty ; 
 int* fan_intercept ; 
 int* fan_min ; 
 int* fan_mode ; 
 int* fan_setpoint ; 
 int* fan_slope ; 
 int /*<<< orphan*/  globalSet (int,int) ; 
 int /*<<< orphan*/  globalSet8bit (int,int) ; 
 scalar_t__ global_row ; 
 scalar_t__ lastPacketTime ; 
 scalar_t__ lastUDPReceivePacketTime ; 
 TYPE_4__* ledpackets ; 
 scalar_t__ minPacketDelay ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  pins_powerctrl ; 
 int /*<<< orphan*/  sendLEDpackets () ; 
 int unpack12bit (int*,int) ; 
 int unpack6bit (int*,int) ; 
 int /*<<< orphan*/ * usarts ; 

void udp_process_recv_packet(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port)
{
    int i, pixValue;
    static int pktCount = 0;
    uint8_t workType;
    uint8_t workParam;

    DEBUGPIN_SET(0);

    pktCount++;

    if (p != NULL) {
        lastUDPReceivePacketTime = LocalTime;
        workType = ((uint8_t*)p->payload)[0];
        switch( workType ) {
            case PKT_TYPE_8BIT_CAL:
                for(i = 0; i < 196*3; i++) {
                    pixValue = ((uint8_t*)p->payload)[16+i];
                    globalSet8bit(i, pixValue);
                }
                break;
            case PKT_TYPE_GSVALS:
                for(i = 0; i < 196*3; i++) {
                    pixValue = unpack12bit(p->payload+16, i);
                    globalSet(i, pixValue);
                }
                break;
            case PKT_TYPE_DOTCORRECT_PACK12:
                for(i = 0; i < 196*3; i++) {
                    pixValue = unpack12bit(p->payload+16, i);
                    globalSet(i, pixValue);
                }
                break;
            case PKT_TYPE_8BIT_RAW:
                for(i = 0; i < 196*3; i++) {
                    pixValue = ((uint8_t*)p->payload)[16+i];
                    globalSet8bit(i, pixValue);
                }
                break;
            case PKT_TYPE_SET_LOOKUP:
                for(i = 0; i < 196*3; i++) {
                    pixValue = unpack12bit(p->payload+16, i);
                    globalSet(i, pixValue);
                }
                workParam = ((uint8_t*)p->payload)[6];
                break;
            case PKT_TYPE_DOTCORRECT_PACK8:
                for(i = 0; i < 196*3; i++) {
                    pixValue = ((uint8_t*)p->payload)[16+i];
                    globalSet(i, pixValue);
                }
                workType = PKT_TYPE_DOTCORRECT_PACK12;
                break;
            case PKT_TYPE_DOTCORRECT_PACK6:
                for(i = 0; i < 196*3; i++) {
                    pixValue = unpack6bit(p->payload+16, i);
                    globalSet(i, pixValue);
                }
                workType = PKT_TYPE_DOTCORRECT_PACK12;
                break;
            case PKT_TYPE_GET_LOOKUP:
                doLookupTableReadback();
                pbuf_free(p);
                DEBUGPIN_CLR(0);
                return;
            case PKT_TYPE_FAN_CONFIG:
                {
                    uint8_t *pl = p->payload+16;
                    for(i = 0; i < 4; i++) {
                        fan_setpoint[i]  = (pl[   i*2] << 8) | pl[   i*2+1];
                        fan_mode[i]      =  pl[ 8+i  ];
                        fan_slope[i]     = (pl[12+i*2] << 8) | pl[12+i*2+1];
                        fan_intercept[i] = (pl[20+i*2] << 8) | pl[20+i*2+1];
                        fan_min[i]       = (pl[28+i*2] << 8) | pl[28+i*2+1];
                        if(fan_mode[i] == 0)
                            fan_duty[i] = fan_setpoint[i];
                    }
                }
                break;
            case PKT_TYPE_RELAY_CTRL:
                if(((uint8_t*)(p->payload+16))[0] != 0)
                    PIN_High(pins_powerctrl, PWR_CTRL_AC_0);
                else
                    PIN_Low(pins_powerctrl, PWR_CTRL_AC_0);

                if(((uint8_t*)(p->payload+16))[1] != 0)
                    PIN_High(pins_powerctrl, PWR_CTRL_AC_1);
                else
                    PIN_Low(pins_powerctrl, PWR_CTRL_AC_1);
                break;
            case PKT_TYPE_REBOOT: // 0xF0
                if( ((uint32_t*)(p->payload+16))[0] == 0x816A4EB2) {
                    if( ((uint8_t*)(p->payload+16))[4] & 0x0F) {
                        ledPacket_type outpkt;
                        outpkt.s.type = PKT_TYPE_REBOOT;
                        ((uint32_t*)outpkt.s.payload)[0] = 0x816A4EB2;
                        ((uint32_t*)outpkt.s.payload)[12] = 0x816A4EB2;
                        ((uint32_t*)outpkt.s.payload)[24] = 0x816A4EB2;
                        ((uint32_t*)outpkt.s.payload)[36] = 0x816A4EB2;
                        ((uint32_t*)outpkt.s.payload)[48] = 0x816A4EB2;
                        for(i = 0; i < 4; i++) {
                            if( ((uint8_t*)(p->payload+16))[4] & (0x01 << i)) {
                                UART_SendBytes(&usarts[i], outpkt.a, sizeof(ledPacket_type));
                            }
                        }
                    }
                    if( ((uint8_t*)(p->payload+16))[4] & 0x10) {
                        Delay(100);  // delay 100ms before rebooting to make sure outgoing packet gets sent completely
                        NVIC_SystemReset();
                    }
                }
                break;
            case PKT_TYPE_BL_INIT:
                if(bootloaderMode == BL_MODE_WAITING) {
                    // need to change bootloader mode and init LED board
                    bootloaderMode = BL_MODE_ACTIVE;
                }

            default:
                workType = 0;
                break;
        }

        // copy the packet type into the packets being sent to each endpoint
        for(i = 0; i < 4; i++) {
            ledpackets[i].s.type = workType;
            ledpackets[i].s.param1 = workParam;
        }

        // limit the rate of communications to the LED board
        if( (global_row != POWER_ROW) && (LocalTime - lastPacketTime >= minPacketDelay) )
            sendLEDpackets();

        /* free the pbuf */
        pbuf_free(p);
    }
    DEBUGPIN_CLR(0);
}