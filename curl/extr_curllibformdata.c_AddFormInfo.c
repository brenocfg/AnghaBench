#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct FormInfo {int dummy; } ;
struct TYPE_5__ {char* value; char* contenttype; struct TYPE_5__* more; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ FormInfo ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPPOST_FILENAME ; 
 TYPE_1__* calloc (int,int) ; 

__attribute__((used)) static FormInfo * AddFormInfo(char *value,
                              char *contenttype,
                              FormInfo *parent_form_info)
{
  FormInfo *form_info;
  form_info = calloc(1, sizeof(struct FormInfo));
  if(form_info) {
    if(value)
      form_info->value = value;
    if(contenttype)
      form_info->contenttype = contenttype;
    form_info->flags = HTTPPOST_FILENAME;
  }
  else
    return NULL;

  if(parent_form_info) {
    /* now, point our 'more' to the original 'more' */
    form_info->more = parent_form_info->more;

    /* then move the original 'more' to point to ourselves */
    parent_form_info->more = form_info;
  }

  return form_info;
}