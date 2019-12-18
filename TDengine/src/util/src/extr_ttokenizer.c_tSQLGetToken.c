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
typedef  size_t uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 size_t TK_BIN ; 
 size_t TK_BITAND ; 
 size_t TK_BITNOT ; 
 size_t TK_BITOR ; 
 size_t TK_BOOL ; 
 size_t TK_COLON ; 
 size_t TK_COMMA ; 
 size_t TK_COMMENT ; 
 size_t TK_CONCAT ; 
 size_t TK_DOT ; 
 size_t TK_EQ ; 
 size_t TK_FLOAT ; 
 size_t TK_GE ; 
 size_t TK_GT ; 
 size_t TK_HEX ; 
 size_t TK_ID ; 
 size_t TK_ILLEGAL ; 
 size_t TK_INTEGER ; 
 size_t TK_IP ; 
 size_t TK_LE ; 
 size_t TK_LP ; 
 size_t TK_LSHIFT ; 
 size_t TK_LT ; 
 size_t TK_MINUS ; 
 size_t TK_NE ; 
 size_t TK_PLUS ; 
 size_t TK_QUESTION ; 
 size_t TK_REM ; 
 size_t TK_RP ; 
 size_t TK_RSHIFT ; 
 size_t TK_SEMI ; 
 size_t TK_SLASH ; 
 size_t TK_SPACE ; 
 size_t TK_STAR ; 
 size_t TK_STRING ; 
 size_t TK_VARIABLE ; 
 int /*<<< orphan*/ * isIdChar ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 size_t tSQLKeywordCode (char*,size_t) ; 

uint32_t tSQLGetToken(char* z, uint32_t* tokenType) {
  uint32_t i;
  switch (*z) {
    case ' ':
    case '\t':
    case '\n':
    case '\f':
    case '\r': {
      for (i = 1; isspace(z[i]); i++) {
      }
      *tokenType = TK_SPACE;
      return i;
    }
    case ':': {
      *tokenType = TK_COLON;
      return 1;
    }
    case '-': {
      if (z[1] == '-') {
        for (i = 2; z[i] && z[i] != '\n'; i++) {
        }
        *tokenType = TK_COMMENT;
        return i;
      }
      *tokenType = TK_MINUS;
      return 1;
    }
    case '(': {
      *tokenType = TK_LP;
      return 1;
    }
    case ')': {
      *tokenType = TK_RP;
      return 1;
    }
    case ';': {
      *tokenType = TK_SEMI;
      return 1;
    }
    case '+': {
      *tokenType = TK_PLUS;
      return 1;
    }
    case '*': {
      *tokenType = TK_STAR;
      return 1;
    }
    case '/': {
      if (z[1] != '*' || z[2] == 0) {
        *tokenType = TK_SLASH;
        return 1;
      }
      for (i = 3; z[i] && (z[i] != '/' || z[i - 1] != '*'); i++) {
      }
      if (z[i]) i++;
      *tokenType = TK_COMMENT;
      return i;
    }
    case '%': {
      *tokenType = TK_REM;
      return 1;
    }
    case '=': {
      *tokenType = TK_EQ;
      return 1 + (z[1] == '=');
    }
    case '<': {
      if (z[1] == '=') {
        *tokenType = TK_LE;
        return 2;
      } else if (z[1] == '>') {
        *tokenType = TK_NE;
        return 2;
      } else if (z[1] == '<') {
        *tokenType = TK_LSHIFT;
        return 2;
      } else {
        *tokenType = TK_LT;
        return 1;
      }
    }
    case '>': {
      if (z[1] == '=') {
        *tokenType = TK_GE;
        return 2;
      } else if (z[1] == '>') {
        *tokenType = TK_RSHIFT;
        return 2;
      } else {
        *tokenType = TK_GT;
        return 1;
      }
    }
    case '!': {
      if (z[1] != '=') {
        *tokenType = TK_ILLEGAL;
        return 2;
      } else {
        *tokenType = TK_NE;
        return 2;
      }
    }
    case '|': {
      if (z[1] != '|') {
        *tokenType = TK_BITOR;
        return 1;
      } else {
        *tokenType = TK_CONCAT;
        return 2;
      }
    }
    case ',': {
      *tokenType = TK_COMMA;
      return 1;
    }
    case '&': {
      *tokenType = TK_BITAND;
      return 1;
    }
    case '~': {
      *tokenType = TK_BITNOT;
      return 1;
    }
    case '?': {
      *tokenType = TK_QUESTION;
      return 1;
    }
    case '\'':
    case '"': {
      int  delim = z[0];
      bool strEnd = false;
      for (i = 1; z[i]; i++) {
        if (z[i] == delim) {
          if (z[i + 1] == delim) {
            i++;
          } else {
            strEnd = true;
            break;
          }
        }
      }
      if (z[i]) i++;

      if (strEnd) {
        *tokenType = TK_STRING;
        return i;
      }

      break;
    }
    case '.': {
      /*
       * handle the the float number with out integer part
       * .123
       * .123e4
       */
      if (isdigit(z[1])) {
        for (i = 2; isdigit(z[i]); i++) {
        }

        if ((z[i] == 'e' || z[i] == 'E') &&
            (isdigit(z[i + 1]) || ((z[i + 1] == '+' || z[i + 1] == '-') && isdigit(z[i + 2])))) {
          i += 2;
          while (isdigit(z[i])) {
            i++;
          }
        }

        *tokenType = TK_FLOAT;
        return i;
      } else {
        *tokenType = TK_DOT;
        return 1;
      }
    }

    case '0': {
      char next = z[1];

      if (next == 'b') { // bin number
        *tokenType = TK_BIN;
        for (i = 2; (z[i] == '0' || z[i] == '1'); ++i) {
        }

        if (i == 2) {
          break;
        }

        return i;
      } else if (next == 'x') {  //hex number
        *tokenType = TK_HEX;
        for (i = 2; isdigit(z[i]) || (z[i] >= 'a' && z[i] <= 'f') || (z[i] >= 'A' && z[i] <= 'F'); ++i) {
        }

        if (i == 2) {
          break;
        }

        return i;
      }
    }
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
      *tokenType = TK_INTEGER;
      for (i = 1; isdigit(z[i]); i++) {
      }

      /* here is the 1a/2s/3m/9y */
      if ((z[i] == 'a' || z[i] == 's' || z[i] == 'm' || z[i] == 'h' || z[i] == 'd' || z[i] == 'n' || z[i] == 'y' ||
          z[i] == 'w' || z[i] == 'A' || z[i] == 'S' || z[i] == 'M' || z[i] == 'H' || z[i] == 'D' || z[i] == 'N' ||
          z[i] == 'Y' || z[i] == 'W') &&
          (isIdChar[z[i + 1]] == 0)) {
        *tokenType = TK_VARIABLE;
        i += 1;
        return i;
      }

      int32_t seg = 1;
      while (z[i] == '.' && isdigit(z[i + 1])) {
        i += 2;
        while (isdigit(z[i])) {
          i++;
        }
        *tokenType = TK_FLOAT;
        seg++;
      }

      if (seg == 4) {  // ip address
        *tokenType = TK_IP;
        return i;
      }

      if ((z[i] == 'e' || z[i] == 'E') &&
          (isdigit(z[i + 1]) || ((z[i + 1] == '+' || z[i + 1] == '-') && isdigit(z[i + 2])))) {
        i += 2;
        while (isdigit(z[i])) {
          i++;
        }
        *tokenType = TK_FLOAT;
      }
      return i;
    }
    case '[': {
      for (i = 1; z[i] && z[i - 1] != ']'; i++) {
      }
      *tokenType = TK_ID;
      return i;
    }
    case 'T':
    case 't':
    case 'F':
    case 'f': {
      for (i = 1; ((z[i] & 0x80) == 0) && isIdChar[z[i]]; i++) {
      }

      if ((i == 4 && strncasecmp(z, "true", 4) == 0) || (i == 5 && strncasecmp(z, "false", 5) == 0)) {
        *tokenType = TK_BOOL;
        return i;
      }
    }
    default: {
      if (((*z & 0x80) != 0) || !isIdChar[*z]) {
        break;
      }
      for (i = 1; ((z[i] & 0x80) == 0) && isIdChar[z[i]]; i++) {
      }
      *tokenType = tSQLKeywordCode(z, i);
      return i;
    }
  }

  *tokenType = TK_ILLEGAL;
  return 0;
}