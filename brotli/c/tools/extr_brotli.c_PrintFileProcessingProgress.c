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
struct TYPE_3__ {int /*<<< orphan*/  total_out; int /*<<< orphan*/  total_in; int /*<<< orphan*/  current_input_path; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  PrintBytes (int /*<<< orphan*/ ) ; 
 char* PrintablePath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void PrintFileProcessingProgress(Context* context) {
  fprintf(stderr, "[%s]: ", PrintablePath(context->current_input_path));
  PrintBytes(context->total_in);
  fprintf(stderr, " -> ");
  PrintBytes(context->total_out);
}