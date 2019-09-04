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
struct TYPE_3__ {int /*<<< orphan*/  force_overwrite; int /*<<< orphan*/  fout; int /*<<< orphan*/  current_output_path; int /*<<< orphan*/  test_integrity; int /*<<< orphan*/  fin; int /*<<< orphan*/  current_input_path; } ;
typedef  TYPE_1__ Context ;
typedef  scalar_t__ BROTLI_BOOL ;

/* Variables and functions */
 scalar_t__ OpenInputFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ OpenOutputFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BROTLI_BOOL OpenFiles(Context* context) {
  BROTLI_BOOL is_ok = OpenInputFile(context->current_input_path, &context->fin);
  if (!context->test_integrity && is_ok) {
    is_ok = OpenOutputFile(
        context->current_output_path, &context->fout, context->force_overwrite);
  }
  return is_ok;
}