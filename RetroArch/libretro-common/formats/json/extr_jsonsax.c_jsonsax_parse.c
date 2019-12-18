#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* json; int /*<<< orphan*/  env; void* ud; TYPE_2__ const* handlers; } ;
typedef  TYPE_1__ state_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* end_document ) (void*) ;int /*<<< orphan*/  (* start_document ) (void*) ;} ;
typedef  TYPE_2__ jsonsax_handlers_t ;

/* Variables and functions */
 int JSONSAX_OK ; 
 int /*<<< orphan*/  jsonx_parse_value (TYPE_1__*) ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

int jsonsax_parse( const char* json, const jsonsax_handlers_t* handlers, void* userdata )
{
  state_t state;
  int res;

  state.json = json;
  state.handlers = handlers;
  state.ud = userdata;

  if ( ( res = setjmp( state.env ) ) == 0 )
  {
    if ( handlers->start_document )
      handlers->start_document( userdata );

    jsonx_parse_value(&state);

    if ( handlers->end_document )
      handlers->end_document( userdata );

    res = JSONSAX_OK;
  }

  return res;
}