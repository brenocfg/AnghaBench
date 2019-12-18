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
struct print_arg {int dummy; } ;
struct event_format {int dummy; } ;
typedef  enum event_type { ____Placeholder_event_type } event_type ;

/* Variables and functions */
 int process_arg_token (struct event_format*,struct print_arg*,char**,int) ; 
 int read_token (char**) ; 

__attribute__((used)) static enum event_type
process_arg(struct event_format *event, struct print_arg *arg, char **tok)
{
	enum event_type type;
	char *token;

	type = read_token(&token);
	*tok = token;

	return process_arg_token(event, arg, tok, type);
}