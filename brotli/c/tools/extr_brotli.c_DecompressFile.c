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
struct TYPE_9__ {scalar_t__ available_in; scalar_t__ verbosity; int /*<<< orphan*/  next_out; int /*<<< orphan*/  available_out; int /*<<< orphan*/  next_in; int /*<<< orphan*/  current_input_path; } ;
typedef  TYPE_1__ Context ;
typedef  int /*<<< orphan*/  BrotliDecoderState ;
typedef  scalar_t__ BrotliDecoderResult ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 scalar_t__ BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT ; 
 scalar_t__ BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT ; 
 scalar_t__ BROTLI_DECODER_RESULT_SUCCESS ; 
 int /*<<< orphan*/  BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 scalar_t__ BrotliDecoderDecompressStream (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushOutput (TYPE_1__*) ; 
 scalar_t__ HasMoreInput (TYPE_1__*) ; 
 int /*<<< orphan*/  InitializeBuffers (TYPE_1__*) ; 
 int /*<<< orphan*/  PrintFileProcessingProgress (TYPE_1__*) ; 
 char* PrintablePath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProvideInput (TYPE_1__*) ; 
 int /*<<< orphan*/  ProvideOutput (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static BROTLI_BOOL DecompressFile(Context* context, BrotliDecoderState* s) {
  BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT;
  InitializeBuffers(context);
  for (;;) {
    if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT) {
      if (!HasMoreInput(context)) {
        fprintf(stderr, "corrupt input [%s]\n",
                PrintablePath(context->current_input_path));
        return BROTLI_FALSE;
      }
      if (!ProvideInput(context)) return BROTLI_FALSE;
    } else if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
      if (!ProvideOutput(context)) return BROTLI_FALSE;
    } else if (result == BROTLI_DECODER_RESULT_SUCCESS) {
      if (!FlushOutput(context)) return BROTLI_FALSE;
      if (context->available_in != 0 || HasMoreInput(context)) {
        fprintf(stderr, "corrupt input [%s]\n",
                PrintablePath(context->current_input_path));
        return BROTLI_FALSE;
      }
      if (context->verbosity > 0) {
        fprintf(stderr, "Decompressed ");
        PrintFileProcessingProgress(context);
        fprintf(stderr, "\n");
      }
      return BROTLI_TRUE;
    } else {
      fprintf(stderr, "corrupt input [%s]\n",
              PrintablePath(context->current_input_path));
      return BROTLI_FALSE;
    }

    result = BrotliDecoderDecompressStream(s, &context->available_in,
        &context->next_in, &context->available_out, &context->next_out, 0);
  }
}