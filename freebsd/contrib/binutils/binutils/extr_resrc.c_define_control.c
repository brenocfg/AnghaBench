#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* rc_uint_type ;
typedef  int /*<<< orphan*/  rc_res_id ;
struct TYPE_3__ {scalar_t__ help; int /*<<< orphan*/ * data; int /*<<< orphan*/  text; int /*<<< orphan*/  class; void* height; void* width; void* y; void* x; void* exstyle; void* style; void* id; int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ rc_dialog_control ;

/* Variables and functions */
 scalar_t__ res_alloc (int) ; 

rc_dialog_control *
define_control (const rc_res_id iid, rc_uint_type id, rc_uint_type x,
		rc_uint_type y, rc_uint_type width, rc_uint_type height,
		const rc_res_id class, rc_uint_type style,
		rc_uint_type exstyle)
{
  rc_dialog_control *n;

  n = (rc_dialog_control *) res_alloc (sizeof (rc_dialog_control));
  n->next = NULL;
  n->id = id;
  n->style = style;
  n->exstyle = exstyle;
  n->x = x;
  n->y = y;
  n->width = width;
  n->height = height;
  n->class = class;
  n->text = iid;
  n->data = NULL;
  n->help = 0;

  return n;
}