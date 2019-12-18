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
struct TYPE_4__ {char* lst; char* buf; } ;
typedef  TYPE_1__ JsonBuf ;

/* Variables and functions */
 char JsonArrStt ; 
 char JsonItmTkn ; 
 char JsonObjStt ; 
 char JsonPairTkn ; 
 int /*<<< orphan*/  httpJsonToken (TYPE_1__*,char) ; 

void httpJsonItemToken(JsonBuf* buf) {
  char c = *(buf->lst - 1);
  if (c == JsonArrStt || c == JsonObjStt || c == JsonPairTkn || c == JsonItmTkn) {
    return;
  }
  if (buf->lst > buf->buf) httpJsonToken(buf, JsonItmTkn);
}