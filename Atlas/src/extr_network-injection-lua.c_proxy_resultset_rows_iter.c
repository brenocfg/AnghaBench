#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_6__* row; TYPE_5__* fields; } ;
typedef  TYPE_2__ proxy_resultset_t ;
struct TYPE_13__ {int offset; TYPE_1__* data; } ;
typedef  TYPE_3__ network_packet ;
typedef  int network_mysqld_lenenc_type ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int guint64 ;
typedef  scalar_t__ gsize ;
struct TYPE_16__ {struct TYPE_16__* next; TYPE_1__* data; } ;
struct TYPE_15__ {scalar_t__ len; } ;
struct TYPE_14__ {TYPE_2__* udata; } ;
struct TYPE_11__ {int len; int str; } ;
typedef  TYPE_4__ GRef ;
typedef  TYPE_5__ GPtrArray ;
typedef  TYPE_6__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
#define  NETWORK_MYSQLD_LENENC_TYPE_EOF 131 
#define  NETWORK_MYSQLD_LENENC_TYPE_ERR 130 
#define  NETWORK_MYSQLD_LENENC_TYPE_INT 129 
#define  NETWORK_MYSQLD_LENENC_TYPE_NULL 128 
 int /*<<< orphan*/  g_return_val_if_fail (int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int /*<<< orphan*/  network_mysqld_proto_get_lenenc_int (TYPE_3__*,int*) ; 
 scalar_t__ network_mysqld_proto_peek_lenenc_type (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  network_mysqld_proto_skip (TYPE_3__*,int) ; 
 scalar_t__ network_mysqld_proto_skip_network_header (TYPE_3__*) ; 

__attribute__((used)) static int proxy_resultset_rows_iter(lua_State *L) {
	GRef *ref = *(GRef **)lua_touserdata(L, lua_upvalueindex(1));
	proxy_resultset_t *res = ref->udata;
	network_packet packet;
	GPtrArray *fields = res->fields;
	gsize i;
	int err = 0;
	network_mysqld_lenenc_type lenenc_type;
    
	GList *chunk = res->row;
    
	g_return_val_if_fail(chunk != NULL, 0);

	packet.data = chunk->data;
	packet.offset = 0;

	err = err || network_mysqld_proto_skip_network_header(&packet);
	err = err || network_mysqld_proto_peek_lenenc_type(&packet, &lenenc_type);
	g_return_val_if_fail(err == 0, 0); /* protocol error */
    
	switch (lenenc_type) {
	case NETWORK_MYSQLD_LENENC_TYPE_ERR:
		/* a ERR packet instead of real rows
		 *
		 * like "explain select fld3 from t2 ignore index (fld3,not_existing)"
		 *
		 * see mysql-test/t/select.test
		 */
	case NETWORK_MYSQLD_LENENC_TYPE_EOF:
		/* if we find the 2nd EOF packet we are done */
		return 0;
	case NETWORK_MYSQLD_LENENC_TYPE_INT:
	case NETWORK_MYSQLD_LENENC_TYPE_NULL:
		break;
	}
    
	lua_newtable(L);
    
	for (i = 0; i < fields->len; i++) {
		guint64 field_len;
        
		err = err || network_mysqld_proto_peek_lenenc_type(&packet, &lenenc_type);
		g_return_val_if_fail(err == 0, 0); /* protocol error */

		switch (lenenc_type) {
		case NETWORK_MYSQLD_LENENC_TYPE_NULL:
			network_mysqld_proto_skip(&packet, 1);
			lua_pushnil(L);
			break;
		case NETWORK_MYSQLD_LENENC_TYPE_INT:
			err = err || network_mysqld_proto_get_lenenc_int(&packet, &field_len);
			err = err || !(field_len <= packet.data->len); /* just to check that we don't overrun by the addition */
			err = err || !(packet.offset + field_len <= packet.data->len); /* check that we have enough string-bytes for the length-encoded string */
			if (err) return luaL_error(L, "%s: row-data is invalid", G_STRLOC);
            
			lua_pushlstring(L, packet.data->str + packet.offset, field_len);

			err = err || network_mysqld_proto_skip(&packet, field_len);
			break;
		default:
			/* EOF and ERR should come up here */
			err = 1;
			break;
		}

		/* lua starts its tables at 1 */
		lua_rawseti(L, -2, i + 1);
		g_return_val_if_fail(err == 0, 0); /* protocol error */
	}
    
	res->row = res->row->next;
    
	return 1;
}