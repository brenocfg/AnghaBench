#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ available_out; } ;
typedef  TYPE_1__ Context ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 int /*<<< orphan*/  WriteOutput (TYPE_1__*) ; 

__attribute__((used)) static BROTLI_BOOL FlushOutput(Context* context) {
  if (!WriteOutput(context)) return BROTLI_FALSE;
  context->available_out = 0;
  return BROTLI_TRUE;
}