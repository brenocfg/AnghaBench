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

/* Variables and functions */
#define  CC608SUB 136 
#define  CC708SUB 135 
#define  IMPORTSRT 134 
#define  IMPORTSSA 133 
#define  PGSSUB 132 
#define  SSASUB 131 
#define  TX3GSUB 130 
#define  UTF8SUB 129 
#define  VOBSUB 128 

const char * hb_subsource_name( int source )
{
    switch (source)
    {
        case VOBSUB:
            return "VOBSUB";
        case IMPORTSRT:
            return "SRT";
        case CC608SUB:
            return "CC608";
        case CC708SUB:
            return "CC708";
        case UTF8SUB:
            return "UTF-8";
        case TX3GSUB:
            return "TX3G";
        case IMPORTSSA:
        case SSASUB:
            return "SSA";
        case PGSSUB:
            return "PGS";
        default:
            return "Unknown";
    }
}