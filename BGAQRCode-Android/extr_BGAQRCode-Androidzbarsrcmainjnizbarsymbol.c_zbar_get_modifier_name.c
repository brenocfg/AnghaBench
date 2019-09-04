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
typedef  int zbar_modifier_t ;

/* Variables and functions */
#define  ZBAR_MOD_AIM 129 
#define  ZBAR_MOD_GS1 128 

const char *zbar_get_modifier_name (zbar_modifier_t mod)
{
    switch(mod) {
    case ZBAR_MOD_GS1: return("GS1");
    case ZBAR_MOD_AIM: return("AIM");
    default: return("");
    }
}