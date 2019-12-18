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
struct config_file {int guaranteed_no_duplicates; scalar_t__ include_depth; int /*<<< orphan*/ * includes; int /*<<< orphan*/ * last; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * entries; int /*<<< orphan*/ * path; } ;
typedef  struct config_file config_file_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

config_file_t *config_file_new_alloc(void)
{
   struct config_file *conf = (struct config_file*)malloc(sizeof(*conf));
   if (!conf)
      return NULL;

   conf->path                     = NULL;
   conf->entries                  = NULL;
   conf->tail                     = NULL;
   conf->last                     = NULL;
   conf->includes                 = NULL;
   conf->include_depth            = 0;
   conf->guaranteed_no_duplicates = false ;

   return conf;
}