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
struct AVTWOFISH {int dummy; } ;

/* Variables and functions */
 struct AVTWOFISH* av_mallocz (int) ; 

struct AVTWOFISH *av_twofish_alloc(void)
{
    return av_mallocz(sizeof(struct AVTWOFISH));
}