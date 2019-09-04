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
#define  POPPLER_ANNOT_MARKUP_REPLY_TYPE_GROUP 129 
#define  POPPLER_ANNOT_MARKUP_REPLY_TYPE_R 128 
 int poppler_annot_markup_get_reply_to (int /*<<< orphan*/ *) ; 

const gchar *
get_markup_reply_to (PopplerAnnotMarkup *poppler_annot)
{
    switch (poppler_annot_markup_get_reply_to (poppler_annot))
    {
      case POPPLER_ANNOT_MARKUP_REPLY_TYPE_R:
        return "Type R";
      case POPPLER_ANNOT_MARKUP_REPLY_TYPE_GROUP:
        return "Type Group";
      default:
        break;
    }

  return "Unknown";
}