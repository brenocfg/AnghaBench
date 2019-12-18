#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct sk_buff {int len; unsigned char* data; } ;
struct TYPE_4__ {int* mdmreg; } ;
struct TYPE_5__ {int mcr; TYPE_1__ emu; struct tty_struct* tty; scalar_t__ online; } ;
typedef  TYPE_2__ modem_info ;

/* Variables and functions */
 int BIT_CPPP ; 
 unsigned char DLE ; 
 int ISDN_AUDIO_SKB_DLECOUNT (struct sk_buff*) ; 
 size_t REG_CPPP ; 
 int TTY_NORMAL ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int tty_buffer_request_room (struct tty_struct*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,char,int) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_struct*,unsigned char*,int) ; 

__attribute__((used)) static int
isdn_tty_try_read(modem_info * info, struct sk_buff *skb)
{
	int c;
	int len;
	struct tty_struct *tty;
	char last;

	if (info->online) {
		if ((tty = info->tty)) {
			if (info->mcr & UART_MCR_RTS) {
				len = skb->len
#ifdef CONFIG_ISDN_AUDIO
					+ ISDN_AUDIO_SKB_DLECOUNT(skb)
#endif
					;

				c = tty_buffer_request_room(tty, len);
				if (c >= len) {
#ifdef CONFIG_ISDN_AUDIO
					if (ISDN_AUDIO_SKB_DLECOUNT(skb)) {
						int l = skb->len;
						unsigned char *dp = skb->data;
						while (--l) {
							if (*dp == DLE)
								tty_insert_flip_char(tty, DLE, 0);
							tty_insert_flip_char(tty, *dp++, 0);
						}
						if (*dp == DLE)
							tty_insert_flip_char(tty, DLE, 0);
						last = *dp;
					} else {
#endif
						if(len > 1)
							tty_insert_flip_string(tty, skb->data, len - 1);
						last = skb->data[len - 1];
#ifdef CONFIG_ISDN_AUDIO
					}
#endif
					if (info->emu.mdmreg[REG_CPPP] & BIT_CPPP)
						tty_insert_flip_char(tty, last, 0xFF);
					else
						tty_insert_flip_char(tty, last, TTY_NORMAL);
					tty_flip_buffer_push(tty);
					kfree_skb(skb);
					return 1;
				}
			}
		}
	}
	return 0;
}