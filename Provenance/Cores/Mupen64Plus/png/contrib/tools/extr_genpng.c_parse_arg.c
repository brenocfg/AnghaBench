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
struct arg {void* y2; void* x2; void* y1; void* x1; int /*<<< orphan*/  width; void* check_fn; void* inside_fn; int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int /*<<< orphan*/  FN_CHECK ; 
 int /*<<< orphan*/  FN_INSIDE ; 
 int /*<<< orphan*/  color_of (char const*) ; 
 void* coordinate_of (char const*) ; 
 void* shape_of (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  width_of (char const*) ; 

__attribute__((used)) static void
parse_arg(struct arg *arg, const char **argv/*7 arguments*/)
{
   /* shape ::= color width shape x1 y1 x2 y2 */
   arg->color = color_of(argv[0]);
   arg->width = width_of(argv[1]);
   arg->inside_fn = shape_of(argv[2], arg->width, FN_INSIDE);
   arg->check_fn = shape_of(argv[2], arg->width, FN_CHECK);
   arg->x1 = coordinate_of(argv[3]);
   arg->y1 = coordinate_of(argv[4]);
   arg->x2 = coordinate_of(argv[5]);
   arg->y2 = coordinate_of(argv[6]);
}