#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_18__ {struct TYPE_18__* next; TYPE_3__* type; } ;
typedef  TYPE_2__ TypeLink ;
struct TYPE_17__ {size_t num_params; int intrinsic; int has_varargs; TYPE_3__* ret; TYPE_3__* varargs_type; int /*<<< orphan*/  params; } ;
struct TYPE_19__ {TYPE_1__ func; int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ Type ;
struct TYPE_20__ {int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_FUNC ; 
 size_t TYPE_PTR ; 
 int /*<<< orphan*/  cached_func_types ; 
 int /*<<< orphan*/  hash_bytes (TYPE_3__**,size_t) ; 
 int hash_mix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_ptr (TYPE_3__*) ; 
 TYPE_2__* map_get_from_uint64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  map_put_from_uint64 (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,TYPE_3__**,size_t) ; 
 int /*<<< orphan*/  memdup (TYPE_3__**,size_t) ; 
 TYPE_3__* type_alloc (int /*<<< orphan*/ ) ; 
 TYPE_5__* type_metrics ; 
 TYPE_2__* xmalloc (int) ; 

Type *type_func(Type **params, size_t num_params, Type *ret, bool intrinsic, bool has_varargs, Type *varargs_type) {
    size_t params_size = num_params * sizeof(*params);
    uint64_t hash = hash_mix(hash_bytes(params, params_size), hash_ptr(ret));
    uint64_t key = hash ? hash : 1;
    TypeLink *cached = map_get_from_uint64(&cached_func_types, key);
    for (TypeLink *it = cached; it; it = it->next) {
        Type *type = it->type;
        if (type->func.num_params == num_params && type->func.ret == ret && type->func.intrinsic == intrinsic && type->func.has_varargs == has_varargs && type->func.varargs_type == varargs_type) {
            if (memcmp(type->func.params, params, params_size) == 0) {
                return type;
            }
        }
    }
    Type *type = type_alloc(TYPE_FUNC);
    type->size = type_metrics[TYPE_PTR].size;
    type->align = type_metrics[TYPE_PTR].align;
    type->func.params = memdup(params, params_size);
    type->func.num_params = num_params;
    type->func.intrinsic = intrinsic;
    type->func.has_varargs = has_varargs;
    type->func.varargs_type = varargs_type;
    type->func.ret = ret;
    TypeLink *new_cached = xmalloc(sizeof(TypeLink));
    new_cached->type = type;
    new_cached->next = cached;
    map_put_from_uint64(&cached_func_types, key, new_cached);
    return type;
}