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
struct TYPE_3__ {char* json; int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLE_2 (char const*,char const*,int) ; 
 int /*<<< orphan*/  JSONSAX_UNTERMINATED_STRING ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void jsonx_parse_string(state_t* state)
{
  const char* string = ++state->json;

  for ( ;; )
  {
    const char* quote = strchr( state->json, '"' );

    if ( !quote )
      longjmp( state->env, JSONSAX_UNTERMINATED_STRING );

    state->json = quote + 1;

    if ( quote[ -1 ] != '\\' )
      break;
  }

  HANDLE_2( string, string, state->json - string - 1 );
}