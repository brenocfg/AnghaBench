#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* sds ;
struct TYPE_10__ {scalar_t__ type; int refcount; scalar_t__ encoding; void* ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_11__ {TYPE_1__** integers; } ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_EMBSTR ; 
 size_t OBJ_ENCODING_EMBSTR_SIZE_LIMIT ; 
 scalar_t__ OBJ_ENCODING_INT ; 
 scalar_t__ OBJ_ENCODING_RAW ; 
 long OBJ_SHARED_INTEGERS ; 
 scalar_t__ OBJ_STRING ; 
 TYPE_1__* createEmbeddedStringObject (void*,size_t) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 int /*<<< orphan*/  incrRefCount (TYPE_1__*) ; 
 int /*<<< orphan*/  sdsEncodedObject (TYPE_1__*) ; 
 void* sdsRemoveFreeSpace (void*) ; 
 size_t sdsavail (void*) ; 
 int /*<<< orphan*/  sdsfree (void*) ; 
 size_t sdslen (void*) ; 
 int /*<<< orphan*/  serverAssertWithInfo (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_4__ shared ; 
 scalar_t__ string2l (void*,size_t,long*) ; 

robj *tryObjectEncoding(robj *o) {
    long value;
    sds s = o->ptr;
    size_t len;

    /* Make sure this is a string object, the only type we encode
     * in this function. Other types use encoded memory efficient
     * representations but are handled by the commands implementing
     * the type. */
    serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);

    /* We try some specialized encoding only for objects that are
     * RAW or EMBSTR encoded, in other words objects that are still
     * in represented by an actually array of chars. */
    if (!sdsEncodedObject(o)) return o;

    /* It's not safe to encode shared objects: shared objects can be shared
     * everywhere in the "object space" of Disque and may end in places where
     * they are not handled. We handle them only as values in the keyspace. */
     if (o->refcount > 1) return o;

    /* Check if we can represent this string as a long integer.
     * Note that we are sure that a string larger than 21 chars is not
     * representable as a 32 nor 64 bit integer. */
    len = sdslen(s);
    if (len <= 21 && string2l(s,len,&value)) {
        /* This object is encodable as a long. Try to use a shared object.
         * Note that we avoid using shared integers when maxmemory is used
         * because every object needs to have a private LRU field for the LRU
         * algorithm to work well. */
        if (value >= 0 && value < OBJ_SHARED_INTEGERS) {
            decrRefCount(o);
            incrRefCount(shared.integers[value]);
            return shared.integers[value];
        } else {
            if (o->encoding == OBJ_ENCODING_RAW) sdsfree(o->ptr);
            o->encoding = OBJ_ENCODING_INT;
            o->ptr = (void*) value;
            return o;
        }
    }

    /* If the string is small and is still RAW encoded,
     * try the EMBSTR encoding which is more efficient.
     * In this representation the object and the SDS string are allocated
     * in the same chunk of memory to save space and cache misses. */
    if (len <= OBJ_ENCODING_EMBSTR_SIZE_LIMIT) {
        robj *emb;

        if (o->encoding == OBJ_ENCODING_EMBSTR) return o;
        emb = createEmbeddedStringObject(s,sdslen(s));
        decrRefCount(o);
        return emb;
    }

    /* We can't encode the object...
     *
     * Do the last try, and at least optimize the SDS string inside
     * the string object to require little space, in case there
     * is more than 10% of free space at the end of the SDS string.
     *
     * We do that only for relatively large strings as this branch
     * is only entered if the length of the string is greater than
     * OBJ_ENCODING_EMBSTR_SIZE_LIMIT. */
    if (o->encoding == OBJ_ENCODING_RAW &&
        sdsavail(s) > len/10)
    {
        o->ptr = sdsRemoveFreeSpace(o->ptr);
    }

    /* Return the original object. */
    return o;
}