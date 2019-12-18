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
struct snmp_context {int dummy; } ;
struct context {struct snmp_context ctx; int /*<<< orphan*/  dlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct context* malloc (int) ; 
 int /*<<< orphan*/  memset (struct context*,int /*<<< orphan*/ ,int) ; 

struct snmp_context *
snmp_init_context(void)
{
	struct context *context;

	if ((context = malloc(sizeof(*context))) == NULL)
		return (NULL);

	memset(context, 0, sizeof(*context));
	TAILQ_INIT(&context->dlist);

	return (&context->ctx);
}