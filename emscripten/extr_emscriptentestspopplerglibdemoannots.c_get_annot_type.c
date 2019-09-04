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
typedef  int /*<<< orphan*/  PopplerAnnot ;

/* Variables and functions */
#define  POPPLER_ANNOT_3D 152 
#define  POPPLER_ANNOT_CARET 151 
#define  POPPLER_ANNOT_CIRCLE 150 
#define  POPPLER_ANNOT_FILE_ATTACHMENT 149 
#define  POPPLER_ANNOT_FREE_TEXT 148 
#define  POPPLER_ANNOT_HIGHLIGHT 147 
#define  POPPLER_ANNOT_INK 146 
#define  POPPLER_ANNOT_LINE 145 
#define  POPPLER_ANNOT_LINK 144 
#define  POPPLER_ANNOT_MOVIE 143 
#define  POPPLER_ANNOT_POLYGON 142 
#define  POPPLER_ANNOT_POLY_LINE 141 
#define  POPPLER_ANNOT_POPUP 140 
#define  POPPLER_ANNOT_PRINTER_MARK 139 
#define  POPPLER_ANNOT_SCREEN 138 
#define  POPPLER_ANNOT_SOUND 137 
#define  POPPLER_ANNOT_SQUARE 136 
#define  POPPLER_ANNOT_SQUIGGLY 135 
#define  POPPLER_ANNOT_STAMP 134 
#define  POPPLER_ANNOT_STRIKE_OUT 133 
#define  POPPLER_ANNOT_TEXT 132 
#define  POPPLER_ANNOT_TRAP_NET 131 
#define  POPPLER_ANNOT_UNDERLINE 130 
#define  POPPLER_ANNOT_WATERMARK 129 
#define  POPPLER_ANNOT_WIDGET 128 
 int poppler_annot_get_annot_type (int /*<<< orphan*/ *) ; 

const gchar *
get_annot_type (PopplerAnnot *poppler_annot)
{
    switch (poppler_annot_get_annot_type (poppler_annot))
    {
      case POPPLER_ANNOT_TEXT:
        return "Text";
      case POPPLER_ANNOT_LINK:
        return "Link";
      case POPPLER_ANNOT_FREE_TEXT:
        return "Free Text";
      case POPPLER_ANNOT_LINE:
        return "Line";
      case POPPLER_ANNOT_SQUARE:
        return "Square";
      case POPPLER_ANNOT_CIRCLE:
        return "Circle";
      case POPPLER_ANNOT_POLYGON:
        return "Polygon";
      case POPPLER_ANNOT_POLY_LINE:
        return "Poly Line";
      case POPPLER_ANNOT_HIGHLIGHT:
        return "Highlight";
      case POPPLER_ANNOT_UNDERLINE:
        return "Underline";
      case POPPLER_ANNOT_SQUIGGLY:
        return "Squiggly";
      case POPPLER_ANNOT_STRIKE_OUT:
        return "Strike Out";
      case POPPLER_ANNOT_STAMP:
        return "Stamp";
      case POPPLER_ANNOT_CARET:
        return "Caret";
      case POPPLER_ANNOT_INK:
        return "Ink";
      case POPPLER_ANNOT_POPUP:
        return "Popup";
      case POPPLER_ANNOT_FILE_ATTACHMENT:
        return "File Attachment";
      case POPPLER_ANNOT_SOUND:
        return "Sound";
      case POPPLER_ANNOT_MOVIE:
        return "Movie";
      case POPPLER_ANNOT_WIDGET:
        return "Widget";
      case POPPLER_ANNOT_SCREEN:
        return "Screen";
      case POPPLER_ANNOT_PRINTER_MARK:
        return "Printer Mark";
      case POPPLER_ANNOT_TRAP_NET:
        return "Trap Net";
      case POPPLER_ANNOT_WATERMARK:
        return "Watermark";
      case POPPLER_ANNOT_3D:
        return "3D";
      default:
        break;
  }

  return "Unknown";
}