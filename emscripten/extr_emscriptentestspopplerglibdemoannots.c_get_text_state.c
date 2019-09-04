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
typedef  int /*<<< orphan*/  PopplerAnnotText ;

/* Variables and functions */
#define  POPPLER_ANNOT_TEXT_STATE_ACCEPTED 135 
#define  POPPLER_ANNOT_TEXT_STATE_CANCELLED 134 
#define  POPPLER_ANNOT_TEXT_STATE_COMPLETED 133 
#define  POPPLER_ANNOT_TEXT_STATE_MARKED 132 
#define  POPPLER_ANNOT_TEXT_STATE_NONE 131 
#define  POPPLER_ANNOT_TEXT_STATE_REJECTED 130 
#define  POPPLER_ANNOT_TEXT_STATE_UNKNOWN 129 
#define  POPPLER_ANNOT_TEXT_STATE_UNMARKED 128 
 int poppler_annot_text_get_state (int /*<<< orphan*/ *) ; 

const gchar *
get_text_state (PopplerAnnotText *poppler_annot)
{
    switch (poppler_annot_text_get_state (poppler_annot))
    {
      case POPPLER_ANNOT_TEXT_STATE_MARKED:
        return "Marked";
      case POPPLER_ANNOT_TEXT_STATE_UNMARKED:
        return "Unmarked";
      case POPPLER_ANNOT_TEXT_STATE_ACCEPTED:
        return "Accepted";
      case POPPLER_ANNOT_TEXT_STATE_REJECTED:
        return "Rejected";
      case POPPLER_ANNOT_TEXT_STATE_CANCELLED:
        return "Cancelled";
      case POPPLER_ANNOT_TEXT_STATE_COMPLETED:
        return "Completed";
      case POPPLER_ANNOT_TEXT_STATE_NONE:
        return "None";
      case POPPLER_ANNOT_TEXT_STATE_UNKNOWN:
        return "Unknown";
      default:
        break;
    }

  return "Unknown";
}