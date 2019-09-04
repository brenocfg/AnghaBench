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
typedef  int /*<<< orphan*/  errmodule_t ;
struct TYPE_3__ {int /*<<< orphan*/  module; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ errinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERRINFO_MAGIC ; 

__attribute__((used)) static inline void err_init (errinfo_t *err,
                             errmodule_t module)
{
    err->magic = ERRINFO_MAGIC;
    err->module = module;
}