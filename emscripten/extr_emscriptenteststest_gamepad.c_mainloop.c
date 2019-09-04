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
struct TYPE_4__ {int index; int numAxes; scalar_t__* axis; int numButtons; scalar_t__* analogButton; scalar_t__* digitalButton; } ;
typedef  TYPE_1__ EmscriptenGamepadEvent ;
typedef  int EMSCRIPTEN_RESULT ;

/* Variables and functions */
 int EMSCRIPTEN_RESULT_SUCCESS ; 
 int /*<<< orphan*/  emscripten_cancel_main_loop () ; 
 int emscripten_get_gamepad_status (int,TYPE_1__*) ; 
 int emscripten_get_num_gamepads () ; 
 int emscripten_sample_gamepad_data () ; 
 int prevNumGamepads ; 
 TYPE_1__* prevState ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void mainloop()
{
  EMSCRIPTEN_RESULT res = emscripten_sample_gamepad_data();
  if (res != EMSCRIPTEN_RESULT_SUCCESS)
  {
    printf("emscripten_sample_gamepad_data returned EMSCRIPTEN_RESULT_NOT_SUPPORTED.\n");
    emscripten_cancel_main_loop();
    return;
  }

  int numGamepads = emscripten_get_num_gamepads();
  if (numGamepads != prevNumGamepads)
  {
    printf("Number of connected gamepads: %d\n", numGamepads);
    prevNumGamepads = numGamepads;
  }

  for(int i = 0; i < numGamepads && i < 32; ++i)
  {
    EmscriptenGamepadEvent ge;
    int ret = emscripten_get_gamepad_status(i, &ge);
    if (ret == EMSCRIPTEN_RESULT_SUCCESS)
    {
      int g = ge.index;
      for(int j = 0; j < ge.numAxes; ++j)
      {
        if (ge.axis[j] != prevState[g].axis[j])
          printf("Gamepad %d, axis %d: %g\n", g, j, ge.axis[j]);
      }

      for(int j = 0; j < ge.numButtons; ++j)
      {
        if (ge.analogButton[j] != prevState[g].analogButton[j] || ge.digitalButton[j] != prevState[g].digitalButton[j])
          printf("Gamepad %d, button %d: Digital: %d, Analog: %g\n", g, j, ge.digitalButton[j], ge.analogButton[j]);
      }
      prevState[g] = ge;
    }
  }
}