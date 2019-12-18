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
struct patch {int addr; int data; } ;

/* Variables and functions */
 char* genie_chars ; 
 char* strchr (char*,char const) ; 

__attribute__((used)) static void genie_decode(const char* code, struct patch* result)
{
  int i = 0, n;
  char* x;

  for(; i < 8; ++i)
  {
    /* If strchr returns NULL, we were given a bad character */
    if(!(x = strchr(genie_chars, code[i])))
    {
      result->addr = -1; result->data = -1;
      return;
    }
    n = (x - genie_chars) >> 1;
    /* Now, based on which character this is, fit it into the result */
    switch(i)
    {
    case 0:
      /* ____ ____ ____ ____ ____ ____ : ____ ____ ABCD E___ */
      result->data |= n << 3;
      break;
    case 1:
      /* ____ ____ DE__ ____ ____ ____ : ____ ____ ____ _ABC */
      result->data |= n >> 2;
      result->addr |= (n & 3) << 14;
      break;
    case 2:
      /* ____ ____ __AB CDE_ ____ ____ : ____ ____ ____ ____ */
      result->addr |= n << 9;
      break;
    case 3:
      /* BCDE ____ ____ ___A ____ ____ : ____ ____ ____ ____ */
      result->addr |= (n & 0xF) << 20 | (n >> 4) << 8;
      break;
    case 4:
      /* ____ ABCD ____ ____ ____ ____ : ___E ____ ____ ____ */
      result->data |= (n & 1) << 12;
      result->addr |= (n >> 1) << 16;
      break;
    case 5:
      /* ____ ____ ____ ____ ____ ____ : E___ ABCD ____ ____ */
      result->data |= (n & 1) << 15 | (n >> 1) << 8;
      break;
    case 6:
      /* ____ ____ ____ ____ CDE_ ____ : _AB_ ____ ____ ____ */
      result->data |= (n >> 3) << 13;
      result->addr |= (n & 7) << 5;
      break;
    case 7:
      /* ____ ____ ____ ____ ___A BCDE : ____ ____ ____ ____ */
      result->addr |= n;
      break;
    }
    /* Go around again */
  }
  return;
}