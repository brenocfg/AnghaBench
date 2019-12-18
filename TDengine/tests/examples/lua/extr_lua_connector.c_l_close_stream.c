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
struct cb_param {int /*<<< orphan*/  stream; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cb_param*) ; 
 struct cb_param* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taos_close_stream (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l_close_stream(lua_State *L){
  //TODO:get stream and free cb_param
  struct cb_param *p = lua_touserdata(L,1);
  taos_close_stream(p->stream);
  free(p);
  return 0;
}