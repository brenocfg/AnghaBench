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
struct TYPE_3__ {scalar_t__ total_out; scalar_t__ total_in; int /*<<< orphan*/  output; int /*<<< orphan*/  next_out; int /*<<< orphan*/  available_out; int /*<<< orphan*/ * next_in; scalar_t__ available_in; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  kFileBufferSize ; 

__attribute__((used)) static void InitializeBuffers(Context* context) {
  context->available_in = 0;
  context->next_in = NULL;
  context->available_out = kFileBufferSize;
  context->next_out = context->output;
  context->total_in = 0;
  context->total_out = 0;
}