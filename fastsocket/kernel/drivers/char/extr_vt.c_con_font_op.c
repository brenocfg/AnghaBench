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
struct vc_data {int dummy; } ;
struct console_font_op {int op; } ;

/* Variables and functions */
 int ENOSYS ; 
#define  KD_FONT_OP_COPY 131 
#define  KD_FONT_OP_GET 130 
#define  KD_FONT_OP_SET 129 
#define  KD_FONT_OP_SET_DEFAULT 128 
 int con_font_copy (struct vc_data*,struct console_font_op*) ; 
 int con_font_default (struct vc_data*,struct console_font_op*) ; 
 int con_font_get (struct vc_data*,struct console_font_op*) ; 
 int con_font_set (struct vc_data*,struct console_font_op*) ; 

int con_font_op(struct vc_data *vc, struct console_font_op *op)
{
	switch (op->op) {
	case KD_FONT_OP_SET:
		return con_font_set(vc, op);
	case KD_FONT_OP_GET:
		return con_font_get(vc, op);
	case KD_FONT_OP_SET_DEFAULT:
		return con_font_default(vc, op);
	case KD_FONT_OP_COPY:
		return con_font_copy(vc, op);
	}
	return -ENOSYS;
}