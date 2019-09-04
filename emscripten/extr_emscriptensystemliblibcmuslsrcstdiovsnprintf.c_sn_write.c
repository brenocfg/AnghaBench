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
struct TYPE_3__ {size_t wend; size_t wpos; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t,unsigned char const*,size_t) ; 

__attribute__((used)) static size_t sn_write(FILE *f, const unsigned char *s, size_t l)
{
	size_t k = f->wend - f->wpos;
	if (k > l) k = l;
	memcpy(f->wpos, s, k);
	f->wpos += k;
	/* pretend to succeed, but discard extra data */
	return l;
}