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
struct arguments {int verbose; int list; char* dumpfile; char** args; } ;
struct argp_state {int arg_num; struct arguments* input; } ;
typedef  int /*<<< orphan*/  error_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARGP_ERR_UNKNOWN ; 
#define  ARGP_KEY_ARG 129 
#define  ARGP_KEY_END 128 
 int /*<<< orphan*/  argp_usage (struct argp_state*) ; 

__attribute__((used)) static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'v':
      arguments->verbose = 1;
      break;
    case 'l':
      arguments->list = 1;
      break;
    case 'd':
      arguments->dumpfile = arg;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 3)
	{
	  argp_usage(state);
	}
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1)
	{
	  argp_usage (state);
	}
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}