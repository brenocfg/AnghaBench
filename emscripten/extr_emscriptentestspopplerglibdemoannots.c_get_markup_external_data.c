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
typedef  int /*<<< orphan*/  PopplerAnnotMarkup ;

/* Variables and functions */
#define  POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_3D 128 
 int poppler_annot_markup_get_external_data (int /*<<< orphan*/ *) ; 

const gchar *
get_markup_external_data (PopplerAnnotMarkup *poppler_annot)
{
    switch (poppler_annot_markup_get_external_data (poppler_annot))
    {
      case POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_3D:
        return "Markup 3D";
      default:
        break;
    }

  return "Unknown";
}