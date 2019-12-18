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
struct AVRC4 {int dummy; } ;
typedef  int /*<<< orphan*/  AVRC4 ;

/* Variables and functions */
 int /*<<< orphan*/ * av_mallocz (int) ; 

AVRC4 *av_rc4_alloc(void)
{
    return av_mallocz(sizeof(struct AVRC4));
}