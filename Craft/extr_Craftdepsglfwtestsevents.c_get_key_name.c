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
#define  GLFW_KEY_0 247 
#define  GLFW_KEY_1 246 
#define  GLFW_KEY_2 245 
#define  GLFW_KEY_3 244 
#define  GLFW_KEY_4 243 
#define  GLFW_KEY_5 242 
#define  GLFW_KEY_6 241 
#define  GLFW_KEY_7 240 
#define  GLFW_KEY_8 239 
#define  GLFW_KEY_9 238 
#define  GLFW_KEY_A 237 
#define  GLFW_KEY_APOSTROPHE 236 
#define  GLFW_KEY_B 235 
#define  GLFW_KEY_BACKSLASH 234 
#define  GLFW_KEY_BACKSPACE 233 
#define  GLFW_KEY_C 232 
#define  GLFW_KEY_CAPS_LOCK 231 
#define  GLFW_KEY_COMMA 230 
#define  GLFW_KEY_D 229 
#define  GLFW_KEY_DELETE 228 
#define  GLFW_KEY_DOWN 227 
#define  GLFW_KEY_E 226 
#define  GLFW_KEY_END 225 
#define  GLFW_KEY_ENTER 224 
#define  GLFW_KEY_EQUAL 223 
#define  GLFW_KEY_ESCAPE 222 
#define  GLFW_KEY_F 221 
#define  GLFW_KEY_F1 220 
#define  GLFW_KEY_F10 219 
#define  GLFW_KEY_F11 218 
#define  GLFW_KEY_F12 217 
#define  GLFW_KEY_F13 216 
#define  GLFW_KEY_F14 215 
#define  GLFW_KEY_F15 214 
#define  GLFW_KEY_F16 213 
#define  GLFW_KEY_F17 212 
#define  GLFW_KEY_F18 211 
#define  GLFW_KEY_F19 210 
#define  GLFW_KEY_F2 209 
#define  GLFW_KEY_F20 208 
#define  GLFW_KEY_F21 207 
#define  GLFW_KEY_F22 206 
#define  GLFW_KEY_F23 205 
#define  GLFW_KEY_F24 204 
#define  GLFW_KEY_F25 203 
#define  GLFW_KEY_F3 202 
#define  GLFW_KEY_F4 201 
#define  GLFW_KEY_F5 200 
#define  GLFW_KEY_F6 199 
#define  GLFW_KEY_F7 198 
#define  GLFW_KEY_F8 197 
#define  GLFW_KEY_F9 196 
#define  GLFW_KEY_G 195 
#define  GLFW_KEY_GRAVE_ACCENT 194 
#define  GLFW_KEY_H 193 
#define  GLFW_KEY_HOME 192 
#define  GLFW_KEY_I 191 
#define  GLFW_KEY_INSERT 190 
#define  GLFW_KEY_J 189 
#define  GLFW_KEY_K 188 
#define  GLFW_KEY_KP_0 187 
#define  GLFW_KEY_KP_1 186 
#define  GLFW_KEY_KP_2 185 
#define  GLFW_KEY_KP_3 184 
#define  GLFW_KEY_KP_4 183 
#define  GLFW_KEY_KP_5 182 
#define  GLFW_KEY_KP_6 181 
#define  GLFW_KEY_KP_7 180 
#define  GLFW_KEY_KP_8 179 
#define  GLFW_KEY_KP_9 178 
#define  GLFW_KEY_KP_ADD 177 
#define  GLFW_KEY_KP_DECIMAL 176 
#define  GLFW_KEY_KP_DIVIDE 175 
#define  GLFW_KEY_KP_ENTER 174 
#define  GLFW_KEY_KP_EQUAL 173 
#define  GLFW_KEY_KP_MULTIPLY 172 
#define  GLFW_KEY_KP_SUBTRACT 171 
#define  GLFW_KEY_L 170 
#define  GLFW_KEY_LEFT 169 
#define  GLFW_KEY_LEFT_ALT 168 
#define  GLFW_KEY_LEFT_BRACKET 167 
#define  GLFW_KEY_LEFT_CONTROL 166 
#define  GLFW_KEY_LEFT_SHIFT 165 
#define  GLFW_KEY_LEFT_SUPER 164 
#define  GLFW_KEY_M 163 
#define  GLFW_KEY_MENU 162 
#define  GLFW_KEY_MINUS 161 
#define  GLFW_KEY_N 160 
#define  GLFW_KEY_NUM_LOCK 159 
#define  GLFW_KEY_O 158 
#define  GLFW_KEY_P 157 
#define  GLFW_KEY_PAGE_DOWN 156 
#define  GLFW_KEY_PAGE_UP 155 
#define  GLFW_KEY_PAUSE 154 
#define  GLFW_KEY_PERIOD 153 
#define  GLFW_KEY_PRINT_SCREEN 152 
#define  GLFW_KEY_Q 151 
#define  GLFW_KEY_R 150 
#define  GLFW_KEY_RIGHT 149 
#define  GLFW_KEY_RIGHT_ALT 148 
#define  GLFW_KEY_RIGHT_BRACKET 147 
#define  GLFW_KEY_RIGHT_CONTROL 146 
#define  GLFW_KEY_RIGHT_SHIFT 145 
#define  GLFW_KEY_RIGHT_SUPER 144 
#define  GLFW_KEY_S 143 
#define  GLFW_KEY_SCROLL_LOCK 142 
#define  GLFW_KEY_SEMICOLON 141 
#define  GLFW_KEY_SLASH 140 
#define  GLFW_KEY_SPACE 139 
#define  GLFW_KEY_T 138 
#define  GLFW_KEY_TAB 137 
#define  GLFW_KEY_U 136 
#define  GLFW_KEY_UP 135 
#define  GLFW_KEY_V 134 
#define  GLFW_KEY_W 133 
#define  GLFW_KEY_WORLD_1 132 
#define  GLFW_KEY_WORLD_2 131 
#define  GLFW_KEY_X 130 
#define  GLFW_KEY_Y 129 
#define  GLFW_KEY_Z 128 

__attribute__((used)) static const char* get_key_name(int key)
{
    switch (key)
    {
        // Printable keys
        case GLFW_KEY_A:            return "A";
        case GLFW_KEY_B:            return "B";
        case GLFW_KEY_C:            return "C";
        case GLFW_KEY_D:            return "D";
        case GLFW_KEY_E:            return "E";
        case GLFW_KEY_F:            return "F";
        case GLFW_KEY_G:            return "G";
        case GLFW_KEY_H:            return "H";
        case GLFW_KEY_I:            return "I";
        case GLFW_KEY_J:            return "J";
        case GLFW_KEY_K:            return "K";
        case GLFW_KEY_L:            return "L";
        case GLFW_KEY_M:            return "M";
        case GLFW_KEY_N:            return "N";
        case GLFW_KEY_O:            return "O";
        case GLFW_KEY_P:            return "P";
        case GLFW_KEY_Q:            return "Q";
        case GLFW_KEY_R:            return "R";
        case GLFW_KEY_S:            return "S";
        case GLFW_KEY_T:            return "T";
        case GLFW_KEY_U:            return "U";
        case GLFW_KEY_V:            return "V";
        case GLFW_KEY_W:            return "W";
        case GLFW_KEY_X:            return "X";
        case GLFW_KEY_Y:            return "Y";
        case GLFW_KEY_Z:            return "Z";
        case GLFW_KEY_1:            return "1";
        case GLFW_KEY_2:            return "2";
        case GLFW_KEY_3:            return "3";
        case GLFW_KEY_4:            return "4";
        case GLFW_KEY_5:            return "5";
        case GLFW_KEY_6:            return "6";
        case GLFW_KEY_7:            return "7";
        case GLFW_KEY_8:            return "8";
        case GLFW_KEY_9:            return "9";
        case GLFW_KEY_0:            return "0";
        case GLFW_KEY_SPACE:        return "SPACE";
        case GLFW_KEY_MINUS:        return "MINUS";
        case GLFW_KEY_EQUAL:        return "EQUAL";
        case GLFW_KEY_LEFT_BRACKET: return "LEFT BRACKET";
        case GLFW_KEY_RIGHT_BRACKET: return "RIGHT BRACKET";
        case GLFW_KEY_BACKSLASH:    return "BACKSLASH";
        case GLFW_KEY_SEMICOLON:    return "SEMICOLON";
        case GLFW_KEY_APOSTROPHE:   return "APOSTROPHE";
        case GLFW_KEY_GRAVE_ACCENT: return "GRAVE ACCENT";
        case GLFW_KEY_COMMA:        return "COMMA";
        case GLFW_KEY_PERIOD:       return "PERIOD";
        case GLFW_KEY_SLASH:        return "SLASH";
        case GLFW_KEY_WORLD_1:      return "WORLD 1";
        case GLFW_KEY_WORLD_2:      return "WORLD 2";

        // Function keys
        case GLFW_KEY_ESCAPE:       return "ESCAPE";
        case GLFW_KEY_F1:           return "F1";
        case GLFW_KEY_F2:           return "F2";
        case GLFW_KEY_F3:           return "F3";
        case GLFW_KEY_F4:           return "F4";
        case GLFW_KEY_F5:           return "F5";
        case GLFW_KEY_F6:           return "F6";
        case GLFW_KEY_F7:           return "F7";
        case GLFW_KEY_F8:           return "F8";
        case GLFW_KEY_F9:           return "F9";
        case GLFW_KEY_F10:          return "F10";
        case GLFW_KEY_F11:          return "F11";
        case GLFW_KEY_F12:          return "F12";
        case GLFW_KEY_F13:          return "F13";
        case GLFW_KEY_F14:          return "F14";
        case GLFW_KEY_F15:          return "F15";
        case GLFW_KEY_F16:          return "F16";
        case GLFW_KEY_F17:          return "F17";
        case GLFW_KEY_F18:          return "F18";
        case GLFW_KEY_F19:          return "F19";
        case GLFW_KEY_F20:          return "F20";
        case GLFW_KEY_F21:          return "F21";
        case GLFW_KEY_F22:          return "F22";
        case GLFW_KEY_F23:          return "F23";
        case GLFW_KEY_F24:          return "F24";
        case GLFW_KEY_F25:          return "F25";
        case GLFW_KEY_UP:           return "UP";
        case GLFW_KEY_DOWN:         return "DOWN";
        case GLFW_KEY_LEFT:         return "LEFT";
        case GLFW_KEY_RIGHT:        return "RIGHT";
        case GLFW_KEY_LEFT_SHIFT:   return "LEFT SHIFT";
        case GLFW_KEY_RIGHT_SHIFT:  return "RIGHT SHIFT";
        case GLFW_KEY_LEFT_CONTROL: return "LEFT CONTROL";
        case GLFW_KEY_RIGHT_CONTROL: return "RIGHT CONTROL";
        case GLFW_KEY_LEFT_ALT:     return "LEFT ALT";
        case GLFW_KEY_RIGHT_ALT:    return "RIGHT ALT";
        case GLFW_KEY_TAB:          return "TAB";
        case GLFW_KEY_ENTER:        return "ENTER";
        case GLFW_KEY_BACKSPACE:    return "BACKSPACE";
        case GLFW_KEY_INSERT:       return "INSERT";
        case GLFW_KEY_DELETE:       return "DELETE";
        case GLFW_KEY_PAGE_UP:      return "PAGE UP";
        case GLFW_KEY_PAGE_DOWN:    return "PAGE DOWN";
        case GLFW_KEY_HOME:         return "HOME";
        case GLFW_KEY_END:          return "END";
        case GLFW_KEY_KP_0:         return "KEYPAD 0";
        case GLFW_KEY_KP_1:         return "KEYPAD 1";
        case GLFW_KEY_KP_2:         return "KEYPAD 2";
        case GLFW_KEY_KP_3:         return "KEYPAD 3";
        case GLFW_KEY_KP_4:         return "KEYPAD 4";
        case GLFW_KEY_KP_5:         return "KEYPAD 5";
        case GLFW_KEY_KP_6:         return "KEYPAD 6";
        case GLFW_KEY_KP_7:         return "KEYPAD 7";
        case GLFW_KEY_KP_8:         return "KEYPAD 8";
        case GLFW_KEY_KP_9:         return "KEYPAD 9";
        case GLFW_KEY_KP_DIVIDE:    return "KEYPAD DIVIDE";
        case GLFW_KEY_KP_MULTIPLY:  return "KEYPAD MULTPLY";
        case GLFW_KEY_KP_SUBTRACT:  return "KEYPAD SUBTRACT";
        case GLFW_KEY_KP_ADD:       return "KEYPAD ADD";
        case GLFW_KEY_KP_DECIMAL:   return "KEYPAD DECIMAL";
        case GLFW_KEY_KP_EQUAL:     return "KEYPAD EQUAL";
        case GLFW_KEY_KP_ENTER:     return "KEYPAD ENTER";
        case GLFW_KEY_PRINT_SCREEN: return "PRINT SCREEN";
        case GLFW_KEY_NUM_LOCK:     return "NUM LOCK";
        case GLFW_KEY_CAPS_LOCK:    return "CAPS LOCK";
        case GLFW_KEY_SCROLL_LOCK:  return "SCROLL LOCK";
        case GLFW_KEY_PAUSE:        return "PAUSE";
        case GLFW_KEY_LEFT_SUPER:   return "LEFT SUPER";
        case GLFW_KEY_RIGHT_SUPER:  return "RIGHT SUPER";
        case GLFW_KEY_MENU:         return "MENU";

        default:                    return "UNKNOWN";
    }
}