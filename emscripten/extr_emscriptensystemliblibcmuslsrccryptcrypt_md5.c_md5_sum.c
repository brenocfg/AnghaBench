#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct md5 {int* h; } ;

/* Variables and functions */
 int /*<<< orphan*/  pad (struct md5*) ; 

__attribute__((used)) static void md5_sum(struct md5 *s, uint8_t *md)
{
	int i;

	pad(s);
	for (i = 0; i < 4; i++) {
		md[4*i] = s->h[i];
		md[4*i+1] = s->h[i] >> 8;
		md[4*i+2] = s->h[i] >> 16;
		md[4*i+3] = s->h[i] >> 24;
	}
}