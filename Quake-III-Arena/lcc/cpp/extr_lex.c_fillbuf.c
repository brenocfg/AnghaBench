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
struct TYPE_3__ {int* inl; scalar_t__ fd; int* inp; scalar_t__ inb; } ;
typedef  TYPE_1__ Source ;

/* Variables and functions */
 int EOB ; 
 int EOF ; 
 void* EOFC ; 
 int /*<<< orphan*/  FATAL ; 
 int INS ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*) ; 
 int read (scalar_t__,char*,int) ; 

int
fillbuf(Source *s)
{
	int n, nr;

	nr = INS/8;
	if ((char *)s->inl+nr > (char *)s->inb+INS)
		error(FATAL, "Input buffer overflow");
	if (s->fd<0 || (n=read(s->fd, (char *)s->inl, INS/8)) <= 0)
		n = 0;
	if ((*s->inp&0xff) == EOB) /* sentinel character appears in input */
		*s->inp = EOFC;
	s->inl += n;
	s->inl[0] = s->inl[1]= s->inl[2]= s->inl[3] = EOB;
	if (n==0) {
		s->inl[0] = s->inl[1]= s->inl[2]= s->inl[3] = EOFC;
		return EOF;
	}
	return 0;
}