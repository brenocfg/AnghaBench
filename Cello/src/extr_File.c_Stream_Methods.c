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
struct Method {char* member_0; char* member_1; char* member_2; } ;

/* Variables and functions */

__attribute__((used)) static struct Method* Stream_Methods(void) {
  
  static struct Method methods[] = {
    {
      "sopen", 
      "var sopen(var self, var resource, var options);",
      "Open the stream `self` with a given `resource` and `options`."
    }, {
      "sclose", 
      "void sclose(var self);",
      "Close the stream `self`."
    }, {
      "sseek", 
      "void sseek(var self, int64_t pos, int origin);",
      "Seek to the position `pos` from some `origin` in the stream `self`."
    }, {
      "stell", 
      "int64_t stell(var self);",
      "Return the current position of the stream `stell`."
    }, {
      "sflush", 
      "void sflush(var self);",
      "Flush the buffered contents of stream `self`."
    }, {
      "seof", 
      "bool seof(var self);",
      "Returns true if there is no more information in the stream."
    }, {
      "sread", 
      "size_t sread(var self, void* output, size_t size);",
      "Read `size` bytes from the stream `self` and write them to `output`."
    }, {
      "swrite", 
      "size_t swrite(var self, void* input, size_t size);",
      "Write `size` bytes to the stream `self` and read them from `input`."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}