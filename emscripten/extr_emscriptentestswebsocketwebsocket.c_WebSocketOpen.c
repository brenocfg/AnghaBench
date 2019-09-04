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
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ EmscriptenWebSocketOpenEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  emscripten_websocket_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_websocket_send_binary (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  emscripten_websocket_send_utf8_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

EM_BOOL WebSocketOpen(int eventType, const EmscriptenWebSocketOpenEvent *e, void *userData)
{
	printf("open(eventType=%d, userData=%d)\n", eventType, (int)userData);

	emscripten_websocket_send_utf8_text(e->socket, "hello on the other side");

	char data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	emscripten_websocket_send_binary(e->socket, data, sizeof(data));

	emscripten_websocket_close(e->socket, 0, 0);
	return 0;
}