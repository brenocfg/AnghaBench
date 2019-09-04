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
struct TYPE_2__ {char* typing_buffer; int suppress_char; int flying; int item_index; int observe1; int player_count; int observe2; scalar_t__ typing; int /*<<< orphan*/ * players; } ;
typedef  int /*<<< orphan*/  Player ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int CRAFT_KEY_FLY ; 
 int CRAFT_KEY_ITEM_NEXT ; 
 int CRAFT_KEY_ITEM_PREV ; 
 int CRAFT_KEY_OBSERVE ; 
 int CRAFT_KEY_OBSERVE_INSET ; 
 char CRAFT_KEY_SIGN ; 
 int /*<<< orphan*/  GLFW_CURSOR ; 
 scalar_t__ GLFW_CURSOR_DISABLED ; 
 int /*<<< orphan*/  GLFW_CURSOR_NORMAL ; 
 int GLFW_KEY_BACKSPACE ; 
 int GLFW_KEY_ENTER ; 
 int GLFW_KEY_ESCAPE ; 
 int GLFW_MOD_CONTROL ; 
 int GLFW_MOD_SHIFT ; 
 int GLFW_MOD_SUPER ; 
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 int MAX_TEXT_LENGTH ; 
 int /*<<< orphan*/  client_talk (char const*) ; 
 TYPE_1__* g ; 
 char* glfwGetClipboardString (int /*<<< orphan*/ *) ; 
 scalar_t__ glfwGetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hit_test_face (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int item_count ; 
 int /*<<< orphan*/  on_left_click () ; 
 int /*<<< orphan*/  on_right_click () ; 
 int /*<<< orphan*/  parse_command (char const*,int) ; 
 int /*<<< orphan*/  set_sign (int,int,int,int,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char const*,char const*,int) ; 

void on_key(GLFWwindow *window, int key, int scancode, int action, int mods) {
    int control = mods & (GLFW_MOD_CONTROL | GLFW_MOD_SUPER);
    int exclusive =
        glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
    if (action == GLFW_RELEASE) {
        return;
    }
    if (key == GLFW_KEY_BACKSPACE) {
        if (g->typing) {
            int n = strlen(g->typing_buffer);
            if (n > 0) {
                g->typing_buffer[n - 1] = '\0';
            }
        }
    }
    if (action != GLFW_PRESS) {
        return;
    }
    if (key == GLFW_KEY_ESCAPE) {
        if (g->typing) {
            g->typing = 0;
        }
        else if (exclusive) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    if (key == GLFW_KEY_ENTER) {
        if (g->typing) {
            if (mods & GLFW_MOD_SHIFT) {
                int n = strlen(g->typing_buffer);
                if (n < MAX_TEXT_LENGTH - 1) {
                    g->typing_buffer[n] = '\r';
                    g->typing_buffer[n + 1] = '\0';
                }
            }
            else {
                g->typing = 0;
                if (g->typing_buffer[0] == CRAFT_KEY_SIGN) {
                    Player *player = g->players;
                    int x, y, z, face;
                    if (hit_test_face(player, &x, &y, &z, &face)) {
                        set_sign(x, y, z, face, g->typing_buffer + 1);
                    }
                }
                else if (g->typing_buffer[0] == '/') {
                    parse_command(g->typing_buffer, 1);
                }
                else {
                    client_talk(g->typing_buffer);
                }
            }
        }
        else {
            if (control) {
                on_right_click();
            }
            else {
                on_left_click();
            }
        }
    }
    if (control && key == 'V') {
        const char *buffer = glfwGetClipboardString(window);
        if (g->typing) {
            g->suppress_char = 1;
            strncat(g->typing_buffer, buffer,
                MAX_TEXT_LENGTH - strlen(g->typing_buffer) - 1);
        }
        else {
            parse_command(buffer, 0);
        }
    }
    if (!g->typing) {
        if (key == CRAFT_KEY_FLY) {
            g->flying = !g->flying;
        }
        if (key >= '1' && key <= '9') {
            g->item_index = key - '1';
        }
        if (key == '0') {
            g->item_index = 9;
        }
        if (key == CRAFT_KEY_ITEM_NEXT) {
            g->item_index = (g->item_index + 1) % item_count;
        }
        if (key == CRAFT_KEY_ITEM_PREV) {
            g->item_index--;
            if (g->item_index < 0) {
                g->item_index = item_count - 1;
            }
        }
        if (key == CRAFT_KEY_OBSERVE) {
            g->observe1 = (g->observe1 + 1) % g->player_count;
        }
        if (key == CRAFT_KEY_OBSERVE_INSET) {
            g->observe2 = (g->observe2 + 1) % g->player_count;
        }
    }
}