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

__attribute__((used)) static const char* Stream_Definition(void) {
  return
    "struct Stream {\n"
    "  var  (*sopen)(var,var,var);\n"
    "  void (*sclose)(var);\n"
    "  void (*sseek)(var,int64_t,int);\n"
    "  int64_t (*stell)(var);\n"
    "  void (*sflush)(var);\n"
    "  bool (*seof)(var);\n"
    "  size_t (*sread)(var,void*,size_t);\n"
    "  size_t (*swrite)(var,void*,size_t);\n"
    "};\n";
}