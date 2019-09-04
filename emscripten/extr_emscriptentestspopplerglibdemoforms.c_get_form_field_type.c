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
typedef  int /*<<< orphan*/  PopplerFormField ;

/* Variables and functions */
#define  POPPLER_FORM_FIELD_BUTTON 132 
#define  POPPLER_FORM_FIELD_CHOICE 131 
#define  POPPLER_FORM_FIELD_SIGNATURE 130 
#define  POPPLER_FORM_FIELD_TEXT 129 
#define  POPPLER_FORM_FIELD_UNKNOWN 128 
 int poppler_form_field_get_field_type (int /*<<< orphan*/ *) ; 

const gchar *
get_form_field_type (PopplerFormField *field)
{
	switch (poppler_form_field_get_field_type (field)) {
	case POPPLER_FORM_FIELD_TEXT:
		return "Text";
	case POPPLER_FORM_FIELD_BUTTON:
		return "Button";
	case POPPLER_FORM_FIELD_CHOICE:
		return "Choice";
	case POPPLER_FORM_FIELD_SIGNATURE:
		return "Signature";
	case POPPLER_FORM_FIELD_UNKNOWN:
	default:
		break;
	}

	return "Unknown";
}