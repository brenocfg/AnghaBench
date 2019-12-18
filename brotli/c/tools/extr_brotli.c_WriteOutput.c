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
struct TYPE_3__ {size_t total_out; int /*<<< orphan*/  current_output_path; int /*<<< orphan*/  fout; scalar_t__ output; scalar_t__ test_integrity; scalar_t__ next_out; } ;
typedef  TYPE_1__ Context ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 char* PrintablePath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  fwrite (scalar_t__,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BROTLI_BOOL WriteOutput(Context* context) {
  size_t out_size = (size_t)(context->next_out - context->output);
  context->total_out += out_size;
  if (out_size == 0) return BROTLI_TRUE;
  if (context->test_integrity) return BROTLI_TRUE;

  fwrite(context->output, 1, out_size, context->fout);
  if (ferror(context->fout)) {
    fprintf(stderr, "failed to write output [%s]: %s\n",
            PrintablePath(context->current_output_path), strerror(errno));
    return BROTLI_FALSE;
  }
  return BROTLI_TRUE;
}