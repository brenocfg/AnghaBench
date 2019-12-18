#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int offset; } ;
typedef  TYPE_1__ rc_parse_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  RC_ALLOC (int,TYPE_1__*) ; 
 int /*<<< orphan*/  rc_destroy_parse_state (TYPE_1__*) ; 
 int /*<<< orphan*/  rc_init_parse_state (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_parse_richpresence_internal (int,char const*,TYPE_1__*) ; 
 int rc_richpresence_t ; 
 int self ; 

int rc_richpresence_size(const char* script) {
  rc_richpresence_t* self;
  rc_parse_state_t parse;
  rc_init_parse_state(&parse, 0, 0, 0);
  
  self = RC_ALLOC(rc_richpresence_t, &parse);
  rc_parse_richpresence_internal(self, script, &parse);

  rc_destroy_parse_state(&parse);
  return parse.offset;
}