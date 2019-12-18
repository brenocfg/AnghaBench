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
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
#define  FORM_ADDR 135 
#define  FORM_BLOCK2 134 
#define  FORM_BLOCK4 133 
#define  FORM_DATA2 132 
#define  FORM_DATA4 131 
#define  FORM_DATA8 130 
 unsigned short FORM_FROM_ATTR (unsigned int) ; 
#define  FORM_REF 129 
#define  FORM_STRING 128 
 int TARGET_FT_POINTER_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objfile ; 
 int /*<<< orphan*/  unknown_attribute_form_complaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int
attribute_size (unsigned int attr)
{
  int nbytes;			/* Size of next data for this attribute */
  unsigned short form;		/* Form of the attribute */

  form = FORM_FROM_ATTR (attr);
  switch (form)
    {
    case FORM_STRING:		/* A variable length field is next */
      nbytes = 0;
      break;
    case FORM_DATA2:		/* Next 2 byte field is the data itself */
    case FORM_BLOCK2:		/* Next 2 byte field is a block length */
      nbytes = 2;
      break;
    case FORM_DATA4:		/* Next 4 byte field is the data itself */
    case FORM_BLOCK4:		/* Next 4 byte field is a block length */
    case FORM_REF:		/* Next 4 byte field is a DIE offset */
      nbytes = 4;
      break;
    case FORM_DATA8:		/* Next 8 byte field is the data itself */
      nbytes = 8;
      break;
    case FORM_ADDR:		/* Next field size is target sizeof(void *) */
      nbytes = TARGET_FT_POINTER_SIZE (objfile);
      break;
    default:
      unknown_attribute_form_complaint (DIE_ID, DIE_NAME, form);
      nbytes = -1;
      break;
    }
  return (nbytes);
}