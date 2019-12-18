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
struct socket {struct cfil_db* so_cfil_db; } ;
struct cfil_db {int /*<<< orphan*/ * cfdb_hashbase; int /*<<< orphan*/  cfdb_hashmask; struct socket* cfdb_so; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFILHASHSIZE ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  M_CFIL ; 
 int /*<<< orphan*/  bzero (struct cfil_db*,int) ; 
 int /*<<< orphan*/  cfil_db_zone ; 
 int /*<<< orphan*/ * hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cfil_db* zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct cfil_db*) ; 

errno_t
cfil_db_init(struct socket *so)
{
    errno_t error = 0;
    struct cfil_db *db = NULL;
    
    CFIL_LOG(LOG_INFO, "");
    
    db = zalloc(cfil_db_zone);
    if (db == NULL) {
        error = ENOMEM;
        goto done;
    }
    bzero(db, sizeof(struct cfil_db));
    db->cfdb_so = so;
    db->cfdb_hashbase = hashinit(CFILHASHSIZE, M_CFIL, &db->cfdb_hashmask);
    if (db->cfdb_hashbase == NULL) {
        zfree(cfil_db_zone, db);
        db = NULL;
        error = ENOMEM;
        goto done;
    }

    so->so_cfil_db = db;

done:
    return (error);
}