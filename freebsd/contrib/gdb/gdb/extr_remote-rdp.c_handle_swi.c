#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n; char* s; } ;
typedef  TYPE_1__ argsin ;

/* Variables and functions */
#define  ABYTE 130 
#define  ASTRING 129 
#define  AWORD 128 
 int /*<<< orphan*/  RDP_OSOpNothing ; 
 int /*<<< orphan*/  RDP_OSOpReply ; 
 int /*<<< orphan*/  RDP_OSOpWord ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ exec_swi (int,TYPE_1__*) ; 
 void* get_byte () ; 
 void* get_word () ; 
 int /*<<< orphan*/  remote_rdp_xfer_inferior_memory (void*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
handle_swi (void)
{
  argsin args[3];
  char *buf;
  int len;
  int count = 0;

  int swino = get_word ();
  int type = get_byte ();
  while (type != 0)
    {
      switch (type & 0x3)
	{
	case ABYTE:
	  args[count].n = get_byte ();
	  break;

	case AWORD:
	  args[count].n = get_word ();
	  break;

	case ASTRING:
	  /* If the word is under 32 bytes it will be sent otherwise
	     an address to it is passed. Also: Special case of 255 */

	  len = get_byte ();
	  if (len > 32)
	    {
	      if (len == 255)
		{
		  len = get_word ();
		}
	      buf = alloca (len);
	      remote_rdp_xfer_inferior_memory (get_word (),
					       buf,
					       len,
					       0,
					       0,
					       0);
	    }
	  else
	    {
	      int i;
	      buf = alloca (len + 1);
	      for (i = 0; i < len; i++)
		buf[i] = get_byte ();
	      buf[i] = 0;
	    }
	  args[count].n = len;
	  args[count].s = buf;
	  break;

	default:
	  error ("Unimplemented SWI argument");
	}

      type = type >> 2;
      count++;
    }

  if (exec_swi (swino, args))
    {
      /* We have two options here reply with either a byte or a word
         which is stored in args[0].n. There is no harm in replying with
         a word all the time, so thats what I do! */
      send_rdp ("bbw-", RDP_OSOpReply, RDP_OSOpWord, args[0].n);
    }
  else
    {
      send_rdp ("bb-", RDP_OSOpReply, RDP_OSOpNothing);
    }
}