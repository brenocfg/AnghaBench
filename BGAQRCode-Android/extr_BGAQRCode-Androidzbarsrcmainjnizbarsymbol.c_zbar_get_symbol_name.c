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
typedef  int zbar_symbol_type_t ;

/* Variables and functions */
#define  ZBAR_CODABAR 145 
#define  ZBAR_CODE128 144 
#define  ZBAR_CODE39 143 
#define  ZBAR_CODE93 142 
#define  ZBAR_COMPOSITE 141 
#define  ZBAR_DATABAR 140 
#define  ZBAR_DATABAR_EXP 139 
#define  ZBAR_EAN13 138 
#define  ZBAR_EAN2 137 
#define  ZBAR_EAN5 136 
#define  ZBAR_EAN8 135 
#define  ZBAR_I25 134 
#define  ZBAR_ISBN10 133 
#define  ZBAR_ISBN13 132 
#define  ZBAR_PDF417 131 
#define  ZBAR_QRCODE 130 
 int ZBAR_SYMBOL ; 
#define  ZBAR_UPCA 129 
#define  ZBAR_UPCE 128 

const char *zbar_get_symbol_name (zbar_symbol_type_t sym)
{
    switch(sym & ZBAR_SYMBOL) {
    case ZBAR_EAN2: return("EAN-2");
    case ZBAR_EAN5: return("EAN-5");
    case ZBAR_EAN8: return("EAN-8");
    case ZBAR_UPCE: return("UPC-E");
    case ZBAR_ISBN10: return("ISBN-10");
    case ZBAR_UPCA: return("UPC-A");
    case ZBAR_EAN13: return("EAN-13");
    case ZBAR_ISBN13: return("ISBN-13");
    case ZBAR_COMPOSITE: return("COMPOSITE");
    case ZBAR_I25: return("I2/5");
    case ZBAR_DATABAR: return("DataBar");
    case ZBAR_DATABAR_EXP: return("DataBar-Exp");
    case ZBAR_CODABAR: return("Codabar");
    case ZBAR_CODE39: return("CODE-39");
    case ZBAR_CODE93: return("CODE-93");
    case ZBAR_CODE128: return("CODE-128");
    case ZBAR_PDF417: return("PDF417");
    case ZBAR_QRCODE: return("QR-Code");
    default: return("UNKNOWN");
    }
}