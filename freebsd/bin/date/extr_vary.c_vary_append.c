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
struct vary {char* arg; struct vary* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ malloc (int) ; 

struct vary *
vary_append(struct vary *v, char *arg)
{
  struct vary *result, **nextp;

  if (v) {
    result = v;
    while (v->next)
      v = v->next;
    nextp = &v->next;
  } else
    nextp = &result;

  if ((*nextp = (struct vary *)malloc(sizeof(struct vary))) == NULL)
    err(1, "malloc");
  (*nextp)->arg = arg;
  (*nextp)->next = NULL;
  return result;
}