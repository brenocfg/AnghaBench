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
typedef  int /*<<< orphan*/  PopplerAnnotFreeText ;

/* Variables and functions */
#define  POPPLER_ANNOT_FREE_TEXT_QUADDING_CENTERED 130 
#define  POPPLER_ANNOT_FREE_TEXT_QUADDING_LEFT_JUSTIFIED 129 
#define  POPPLER_ANNOT_FREE_TEXT_QUADDING_RIGHT_JUSTIFIED 128 
 int poppler_annot_free_text_get_quadding (int /*<<< orphan*/ *) ; 

const gchar *
get_free_text_quadding (PopplerAnnotFreeText *poppler_annot)
{
    switch (poppler_annot_free_text_get_quadding (poppler_annot))
    {
      case POPPLER_ANNOT_FREE_TEXT_QUADDING_LEFT_JUSTIFIED:
        return "Left Justified";
      case POPPLER_ANNOT_FREE_TEXT_QUADDING_CENTERED:
        return "Centered";
      case POPPLER_ANNOT_FREE_TEXT_QUADDING_RIGHT_JUSTIFIED:
        return "Right Justified";
      default:
        break;
    }

  return "Unknown";
}