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
typedef  int zbar_config_t ;

/* Variables and functions */
#define  ZBAR_CFG_ADD_CHECK 137 
#define  ZBAR_CFG_ASCII 136 
#define  ZBAR_CFG_EMIT_CHECK 135 
#define  ZBAR_CFG_ENABLE 134 
#define  ZBAR_CFG_MAX_LEN 133 
#define  ZBAR_CFG_MIN_LEN 132 
#define  ZBAR_CFG_POSITION 131 
#define  ZBAR_CFG_UNCERTAINTY 130 
#define  ZBAR_CFG_X_DENSITY 129 
#define  ZBAR_CFG_Y_DENSITY 128 

const char *zbar_get_config_name (zbar_config_t cfg)
{
    switch(cfg) {
    case ZBAR_CFG_ENABLE: return("ENABLE");
    case ZBAR_CFG_ADD_CHECK: return("ADD_CHECK");
    case ZBAR_CFG_EMIT_CHECK: return("EMIT_CHECK");
    case ZBAR_CFG_ASCII: return("ASCII");
    case ZBAR_CFG_MIN_LEN: return("MIN_LEN");
    case ZBAR_CFG_MAX_LEN: return("MAX_LEN");
    case ZBAR_CFG_UNCERTAINTY: return("UNCERTAINTY");
    case ZBAR_CFG_POSITION: return("POSITION");
    case ZBAR_CFG_X_DENSITY: return("X_DENSITY");
    case ZBAR_CFG_Y_DENSITY: return("Y_DENSITY");
    default: return("");
    }
}