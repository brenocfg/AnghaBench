#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int tcflag_t ;
struct TYPE_6__ {TYPE_2__* tty; } ;
struct e100_serial {int char_time_usec; int baud; int flush_time_usec; TYPE_3__ port; } ;
struct TYPE_5__ {TYPE_1__* termios; } ;
struct TYPE_4__ {int c_cflag; } ;

/* Variables and functions */
 int CS7 ; 
 int CSIZE ; 
 int CSTOPB ; 
 int MIN_FLUSH_TIME_USEC ; 
 int PARENB ; 

__attribute__((used)) static void update_char_time(struct e100_serial * info)
{
	tcflag_t cflags = info->port.tty->termios->c_cflag;
	int bits;

	/* calc. number of bits / data byte */
	/* databits + startbit and 1 stopbit */
	if ((cflags & CSIZE) == CS7)
		bits = 9;
	else
		bits = 10;

	if (cflags & CSTOPB)     /* 2 stopbits ? */
		bits++;

	if (cflags & PARENB)     /* parity bit ? */
		bits++;

	/* calc timeout */
	info->char_time_usec = ((bits * 1000000) / info->baud) + 1;
	info->flush_time_usec = 4*info->char_time_usec;
	if (info->flush_time_usec < MIN_FLUSH_TIME_USEC)
		info->flush_time_usec = MIN_FLUSH_TIME_USEC;

}