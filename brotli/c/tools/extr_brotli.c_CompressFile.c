#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ available_in; scalar_t__ available_out; scalar_t__ verbosity; int /*<<< orphan*/  current_input_path; int /*<<< orphan*/  next_out; int /*<<< orphan*/  next_in; } ;
typedef  TYPE_1__ Context ;
typedef  int /*<<< orphan*/  BrotliEncoderState ;
typedef  int BROTLI_BOOL ;

/* Variables and functions */
 int BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_OPERATION_FINISH ; 
 int /*<<< orphan*/  BROTLI_OPERATION_PROCESS ; 
 int BROTLI_TRUE ; 
 int /*<<< orphan*/  BrotliEncoderCompressStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BrotliEncoderIsFinished (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FlushOutput (TYPE_1__*) ; 
 int /*<<< orphan*/  HasMoreInput (TYPE_1__*) ; 
 int /*<<< orphan*/  InitializeBuffers (TYPE_1__*) ; 
 int /*<<< orphan*/  PrintFileProcessingProgress (TYPE_1__*) ; 
 char* PrintablePath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProvideInput (TYPE_1__*) ; 
 int /*<<< orphan*/  ProvideOutput (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static BROTLI_BOOL CompressFile(Context* context, BrotliEncoderState* s) {
  BROTLI_BOOL is_eof = BROTLI_FALSE;
  InitializeBuffers(context);
  for (;;) {
    if (context->available_in == 0 && !is_eof) {
      if (!ProvideInput(context)) return BROTLI_FALSE;
      is_eof = !HasMoreInput(context);
    }

    if (!BrotliEncoderCompressStream(s,
        is_eof ? BROTLI_OPERATION_FINISH : BROTLI_OPERATION_PROCESS,
        &context->available_in, &context->next_in,
        &context->available_out, &context->next_out, NULL)) {
      /* Should detect OOM? */
      fprintf(stderr, "failed to compress data [%s]\n",
              PrintablePath(context->current_input_path));
      return BROTLI_FALSE;
    }

    if (context->available_out == 0) {
      if (!ProvideOutput(context)) return BROTLI_FALSE;
    }

    if (BrotliEncoderIsFinished(s)) {
      if (!FlushOutput(context)) return BROTLI_FALSE;
      if (context->verbosity > 0) {
        fprintf(stderr, "Compressed ");
        PrintFileProcessingProgress(context);
        fprintf(stderr, "\n");
      }
      return BROTLI_TRUE;
    }
  }
}