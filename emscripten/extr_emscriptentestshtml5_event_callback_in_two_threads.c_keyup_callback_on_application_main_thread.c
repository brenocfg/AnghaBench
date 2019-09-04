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
struct TYPE_3__ {int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ EmscriptenKeyboardEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int DOM_PK_ENTER ; 
 int /*<<< orphan*/  ReportResult (int) ; 
 void* application_main_thread_id ; 
 int /*<<< orphan*/  assert (int) ; 
 int emscripten_compute_dom_pk_code (int /*<<< orphan*/ ) ; 
 char* emscripten_dom_pk_code_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ pthread_self () ; 
 int /*<<< orphan*/  saw_keydown_event_on_enter_key_on_application_main_thread ; 
 int /*<<< orphan*/  saw_keydown_event_on_enter_key_on_main_browser_thread ; 
 scalar_t__ saw_keypress_event_on_enter_key ; 

EM_BOOL keyup_callback_on_application_main_thread(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
  int dom_pk_code = emscripten_compute_dom_pk_code(e->code);
  printf("keyup_callback_on_application_main_thread received on pthread: %p, application_main_thread_id; %p, dom_pk_code: %s\n", (void*)pthread_self(), application_main_thread_id, emscripten_dom_pk_code_to_string(dom_pk_code));
  assert((void*)pthread_self() == application_main_thread_id);

  if (dom_pk_code == DOM_PK_ENTER)
  {
    if (!saw_keydown_event_on_enter_key_on_application_main_thread)
    {
      printf("Test failed! KeyUp event came through, but a KeyDown event should have first been processed on the application main thread!\n");
      ReportResult(12346); // FAIL
    }
    if (!saw_keydown_event_on_enter_key_on_main_browser_thread)
    {
      printf("Test failed! KeyUp event came through, but a KeyDown event should have first been processed on the main browser thread!\n");
      ReportResult(12347); // FAIL      
    }
    if (saw_keypress_event_on_enter_key)
    {
      printf("Test failed! KeyUp event came through, but a KeyPress event was first seen, suppressing it did not work!\n");
      ReportResult(12348); // FAIL
    }
    printf("Test passed!\n");
    ReportResult(1); // PASS
  }
  return 0;
}