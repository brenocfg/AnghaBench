#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int typing; char* typing_buffer; scalar_t__ suppress_char; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 unsigned int CRAFT_KEY_CHAT ; 
 unsigned int CRAFT_KEY_COMMAND ; 
 unsigned int CRAFT_KEY_SIGN ; 
 int MAX_TEXT_LENGTH ; 
 TYPE_1__* g ; 
 int strlen (char*) ; 

void on_char(GLFWwindow *window, unsigned int u) {
    if (g->suppress_char) {
        g->suppress_char = 0;
        return;
    }
    if (g->typing) {
        if (u >= 32 && u < 128) {
            char c = (char)u;
            int n = strlen(g->typing_buffer);
            if (n < MAX_TEXT_LENGTH - 1) {
                g->typing_buffer[n] = c;
                g->typing_buffer[n + 1] = '\0';
            }
        }
    }
    else {
        if (u == CRAFT_KEY_CHAT) {
            g->typing = 1;
            g->typing_buffer[0] = '\0';
        }
        if (u == CRAFT_KEY_COMMAND) {
            g->typing = 1;
            g->typing_buffer[0] = '/';
            g->typing_buffer[1] = '\0';
        }
        if (u == CRAFT_KEY_SIGN) {
            g->typing = 1;
            g->typing_buffer[0] = CRAFT_KEY_SIGN;
            g->typing_buffer[1] = '\0';
        }
    }
}