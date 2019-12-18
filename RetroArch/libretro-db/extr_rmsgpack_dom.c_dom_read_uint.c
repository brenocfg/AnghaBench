#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  uint_; } ;
struct rmsgpack_dom_value {TYPE_1__ val; int /*<<< orphan*/  type; } ;
struct dom_reader_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDT_UINT ; 
 scalar_t__ dom_reader_state_pop (struct dom_reader_state*) ; 

__attribute__((used)) static int dom_read_uint(uint64_t value, void *data)
{
   struct dom_reader_state *dom_state = (struct dom_reader_state *)data;
   struct rmsgpack_dom_value *v =
      (struct rmsgpack_dom_value*)dom_reader_state_pop(dom_state);

   v->type = RDT_UINT;
   v->val.uint_ = value;
   return 0;
}