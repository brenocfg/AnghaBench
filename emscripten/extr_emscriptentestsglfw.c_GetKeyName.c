#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  GLFW_KEY_BACKSPACE 199 
#define  GLFW_KEY_CAPS_LOCK 198 
#define  GLFW_KEY_DEL 197 
#define  GLFW_KEY_DOWN 196 
#define  GLFW_KEY_END 195 
#define  GLFW_KEY_ENTER 194 
#define  GLFW_KEY_ESC 193 
#define  GLFW_KEY_F1 192 
#define  GLFW_KEY_F10 191 
#define  GLFW_KEY_F11 190 
#define  GLFW_KEY_F12 189 
#define  GLFW_KEY_F13 188 
#define  GLFW_KEY_F14 187 
#define  GLFW_KEY_F15 186 
#define  GLFW_KEY_F16 185 
#define  GLFW_KEY_F17 184 
#define  GLFW_KEY_F18 183 
#define  GLFW_KEY_F19 182 
#define  GLFW_KEY_F2 181 
#define  GLFW_KEY_F20 180 
#define  GLFW_KEY_F21 179 
#define  GLFW_KEY_F22 178 
#define  GLFW_KEY_F23 177 
#define  GLFW_KEY_F24 176 
#define  GLFW_KEY_F25 175 
#define  GLFW_KEY_F3 174 
#define  GLFW_KEY_F4 173 
#define  GLFW_KEY_F5 172 
#define  GLFW_KEY_F6 171 
#define  GLFW_KEY_F7 170 
#define  GLFW_KEY_F8 169 
#define  GLFW_KEY_F9 168 
#define  GLFW_KEY_HOME 167 
#define  GLFW_KEY_INSERT 166 
#define  GLFW_KEY_KP_0 165 
#define  GLFW_KEY_KP_1 164 
#define  GLFW_KEY_KP_2 163 
#define  GLFW_KEY_KP_3 162 
#define  GLFW_KEY_KP_4 161 
#define  GLFW_KEY_KP_5 160 
#define  GLFW_KEY_KP_6 159 
#define  GLFW_KEY_KP_7 158 
#define  GLFW_KEY_KP_8 157 
#define  GLFW_KEY_KP_9 156 
#define  GLFW_KEY_KP_ADD 155 
#define  GLFW_KEY_KP_DECIMAL 154 
#define  GLFW_KEY_KP_DIVIDE 153 
#define  GLFW_KEY_KP_ENTER 152 
#define  GLFW_KEY_KP_EQUAL 151 
#define  GLFW_KEY_KP_MULTIPLY 150 
#define  GLFW_KEY_KP_NUM_LOCK 149 
#define  GLFW_KEY_KP_SUBTRACT 148 
#define  GLFW_KEY_LALT 147 
#define  GLFW_KEY_LCTRL 146 
#define  GLFW_KEY_LEFT 145 
#define  GLFW_KEY_LSHIFT 144 
#define  GLFW_KEY_LSUPER 143 
#define  GLFW_KEY_MENU 142 
#define  GLFW_KEY_PAGEDOWN 141 
#define  GLFW_KEY_PAGEUP 140 
#define  GLFW_KEY_PAUSE 139 
#define  GLFW_KEY_RALT 138 
#define  GLFW_KEY_RCTRL 137 
#define  GLFW_KEY_RIGHT 136 
#define  GLFW_KEY_RSHIFT 135 
#define  GLFW_KEY_RSUPER 134 
#define  GLFW_KEY_SCROLL_LOCK 133 
#define  GLFW_KEY_SPACE 132 
#define  GLFW_KEY_SPECIAL 131 
#define  GLFW_KEY_TAB 130 
#define  GLFW_KEY_UNKNOWN 129 
#define  GLFW_KEY_UP 128 
 char* malloc (int) ; 

char* GetKeyName(int key){
  switch(key){
    case GLFW_KEY_UNKNOWN: return "unknown";
    case GLFW_KEY_SPACE: return "space";
    case GLFW_KEY_SPECIAL: return "special";
    case GLFW_KEY_ESC: return "escape";
    case GLFW_KEY_F1 : return "F1";
    case GLFW_KEY_F2 : return "F2";
    case GLFW_KEY_F3 : return "F3";
    case GLFW_KEY_F4 : return "F4";
    case GLFW_KEY_F5 : return "F5";
    case GLFW_KEY_F6 : return "F6";
    case GLFW_KEY_F7 : return "F7";
    case GLFW_KEY_F8 : return "F8";
    case GLFW_KEY_F9 : return "F9";
    case GLFW_KEY_F10: return "F10";
    case GLFW_KEY_F11: return "F11";
    case GLFW_KEY_F12: return "F12";
    case GLFW_KEY_F13: return "F13";
    case GLFW_KEY_F14: return "F14";
    case GLFW_KEY_F15: return "F15";
    case GLFW_KEY_F16: return "F16";
    case GLFW_KEY_F17: return "F17";
    case GLFW_KEY_F18: return "F18";
    case GLFW_KEY_F19: return "F19";
    case GLFW_KEY_F20: return "F20";
    case GLFW_KEY_F21: return "F21";
    case GLFW_KEY_F22: return "F22";
    case GLFW_KEY_F23: return "F23";
    case GLFW_KEY_F24: return "F24";
    case GLFW_KEY_F25: return "F25";
    case GLFW_KEY_UP : return "up";
    case GLFW_KEY_DOWN: return "down";
    case GLFW_KEY_LEFT: return "left";
    case GLFW_KEY_RIGHT: return "right";
    case GLFW_KEY_LSHIFT: return "left shift";
    case GLFW_KEY_RSHIFT: return "right shift";
    case GLFW_KEY_LCTRL: return "left ctrl";
    case GLFW_KEY_RCTRL: return "right ctrl";
    case GLFW_KEY_LALT: return "left alt";
    case GLFW_KEY_RALT: return "right alt";
    case GLFW_KEY_TAB: return "tab";
    case GLFW_KEY_ENTER: return "enter";
    case GLFW_KEY_BACKSPACE: return "backspace";
    case GLFW_KEY_INSERT: return "insertr";
    case GLFW_KEY_DEL: return "del";
    case GLFW_KEY_PAGEUP: return "page up";
    case GLFW_KEY_PAGEDOWN: return "page down";
    case GLFW_KEY_HOME: return "home";
    case GLFW_KEY_END: return "end";
    case GLFW_KEY_KP_0: return "0";
    case GLFW_KEY_KP_1: return "1";
    case GLFW_KEY_KP_2: return "2";
    case GLFW_KEY_KP_3: return "3";
    case GLFW_KEY_KP_4: return "4";
    case GLFW_KEY_KP_5: return "5";
    case GLFW_KEY_KP_6: return "6";
    case GLFW_KEY_KP_7: return "7";
    case GLFW_KEY_KP_8: return "8";
    case GLFW_KEY_KP_9: return "9";
    case GLFW_KEY_KP_DIVIDE: return "/";
    case GLFW_KEY_KP_MULTIPLY: return "*";
    case GLFW_KEY_KP_SUBTRACT: return "-";
    case GLFW_KEY_KP_ADD: return "+";
    case GLFW_KEY_KP_DECIMAL: return ".";
    case GLFW_KEY_KP_EQUAL: return "=";
    case GLFW_KEY_KP_ENTER: return "enter";
    case GLFW_KEY_KP_NUM_LOCK: return "num lock";
    case GLFW_KEY_CAPS_LOCK: return "caps lock";
    case GLFW_KEY_SCROLL_LOCK: return "scroll lock";
    case GLFW_KEY_PAUSE: return "pause";
    case GLFW_KEY_LSUPER: return "left super";
    case GLFW_KEY_RSUPER: return "right super";
    case GLFW_KEY_MENU: return "menu";
    }
    char* chr = malloc(2*sizeof(char));
    chr[0] = key;
    chr[1] = '\0';
    return chr;
}