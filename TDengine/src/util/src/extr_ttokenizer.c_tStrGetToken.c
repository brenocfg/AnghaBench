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
typedef  size_t uint32_t ;
typedef  size_t int32_t ;
struct TYPE_3__ {size_t n; size_t type; char* z; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
 size_t TK_FLOAT ; 
 scalar_t__ TK_ID ; 
 scalar_t__ TK_ILLEGAL ; 
 size_t TK_INTEGER ; 
 scalar_t__ TK_MINUS ; 
 scalar_t__ TK_PLUS ; 
 scalar_t__ TK_SEMI ; 
 scalar_t__ TK_STRING ; 
 void* tSQLGetToken (char*,size_t*) ; 

SSQLToken tStrGetToken(char* str, int32_t* i, bool isPrevOptr, uint32_t numOfIgnoreToken, uint32_t* ignoreTokenTypes) {
  SSQLToken t0 = {0};

  // here we reach the end of sql string, null-terminated string
  if (str[*i] == 0) {
    t0.n = 0;
    return t0;
  }

  // IGNORE TK_SPACE, TK_COMMA, and specified tokens
  while (1) {
    *i += t0.n;

    bool hasComma = false;
    while ((str[*i] == ' ' || str[*i] == '\n' || str[*i] == '\r' || str[*i] == '\t' || str[*i] == '\f')
        || str[*i] == ',') {
      if (str[*i] == ',') {
        if (false == hasComma) {
          hasComma = true;
        } else {  // comma only allowed once
          t0.n = 0;
          return t0;
        }
      }
      (*i)++;
    }

    t0.n = tSQLGetToken(&str[*i], &t0.type);

    bool ignoreFlag = false;
    for (uint32_t k = 0; k < numOfIgnoreToken; k++) {
      if (t0.type == ignoreTokenTypes[k]) {
        ignoreFlag = true;
        break;
      }
    }

    if (!ignoreFlag) {
      break;
    }
  }

  if (t0.type == TK_SEMI) {
    t0.n = 0;
    return t0;
  }

  uint32_t type = 0;
  int32_t  len;

  // support parse the 'db.tbl' format, notes: There should be no space on either side of the dot!
  if ('.' == str[*i + t0.n]) {
    len = tSQLGetToken(&str[*i + t0.n + 1], &type);

    // only id and string are valid
    if ((TK_STRING != t0.type) && (TK_ID != t0.type)) {
      t0.type = TK_ILLEGAL;
      t0.n = 0;

      return t0;
    }

    t0.n += len + 1;

  } else {
    // support parse the -/+number format
    if ((isPrevOptr) && (t0.type == TK_MINUS || t0.type == TK_PLUS)) {
      len = tSQLGetToken(&str[*i + t0.n], &type);
      if (type == TK_INTEGER || type == TK_FLOAT) {
        t0.type = type;
        t0.n += len;
      }
    }
  }

  t0.z = str + (*i);
  *i += t0.n;

  return t0;
}