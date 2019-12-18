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
typedef  int Type ;

/* Variables and functions */
#define  BFF 131 
#define  PROGRESSIVE 130 
#define  TFF 129 
#define  UNDETERMINED 128 

__attribute__((used)) static const char *type2str(Type type)
{
    switch(type) {
        case TFF          : return "tff";
        case BFF          : return "bff";
        case PROGRESSIVE  : return "progressive";
        case UNDETERMINED : return "undetermined";
    }
    return NULL;
}