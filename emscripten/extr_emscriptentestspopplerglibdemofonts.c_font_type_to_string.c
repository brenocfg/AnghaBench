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
typedef  char gchar ;
typedef  int PopplerFontType ;

/* Variables and functions */
#define  POPPLER_FONT_TYPE_CID_TYPE0 134 
#define  POPPLER_FONT_TYPE_CID_TYPE0C 133 
#define  POPPLER_FONT_TYPE_CID_TYPE2 132 
#define  POPPLER_FONT_TYPE_TRUETYPE 131 
#define  POPPLER_FONT_TYPE_TYPE1 130 
#define  POPPLER_FONT_TYPE_TYPE1C 129 
#define  POPPLER_FONT_TYPE_TYPE3 128 

__attribute__((used)) static const gchar *
font_type_to_string (PopplerFontType type)
{
	switch (type) {
	case POPPLER_FONT_TYPE_TYPE1:
		return "Type 1";
	case POPPLER_FONT_TYPE_TYPE1C:
		return "Type 1C";
	case POPPLER_FONT_TYPE_TYPE3:
		return "Type 3";
	case POPPLER_FONT_TYPE_TRUETYPE:
		return "TrueType";
	case POPPLER_FONT_TYPE_CID_TYPE0:
		return "Type 1 (CID)";
	case POPPLER_FONT_TYPE_CID_TYPE0C:
		return "Type 1C (CID)";
	case POPPLER_FONT_TYPE_CID_TYPE2:
		return "TrueType (CID)";
	default:
		return "Unknown font type";
	}
}