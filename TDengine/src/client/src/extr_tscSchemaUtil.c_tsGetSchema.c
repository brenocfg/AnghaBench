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
struct SSchema {int dummy; } ;
typedef  int /*<<< orphan*/  SMeterMeta ;

/* Variables and functions */
 struct SSchema* tsGetColumnSchema (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct SSchema* tsGetSchema(SMeterMeta* pMeta) {
  if (pMeta == NULL) {
    return NULL;
  }
  return tsGetColumnSchema(pMeta, 0);
}