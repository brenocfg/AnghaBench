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
 int* aKWCode ; 
 scalar_t__* aKWHash ; 
 int* aKWLen ; 
 scalar_t__* aKWNext ; 
 size_t* aKWOffset ; 
 int charMap (char const) ; 
 int /*<<< orphan*/  testcase (int) ; 
 char const toupper (char const) ; 
 char* zKWText ; 

__attribute__((used)) static int keywordCode(const char *z, int n, int *pType){
  int i, j;
  const char *zKW;
  if( n>=2 ){
    i = ((charMap(z[0])*4) ^ (charMap(z[n-1])*3) ^ n) % 127;
    for(i=((int)aKWHash[i])-1; i>=0; i=((int)aKWNext[i])-1){
      if( aKWLen[i]!=n ) continue;
      j = 0;
      zKW = &zKWText[aKWOffset[i]];
#ifdef SQLITE_ASCII
      while( j<n && (z[j]&~0x20)==zKW[j] ){ j++; }
#endif
#ifdef SQLITE_EBCDIC
      while( j<n && toupper(z[j])==zKW[j] ){ j++; }
#endif
      if( j<n ) continue;
      testcase( i==0 ); /* REINDEX */
      testcase( i==1 ); /* INDEXED */
      testcase( i==2 ); /* INDEX */
      testcase( i==3 ); /* DESC */
      testcase( i==4 ); /* ESCAPE */
      testcase( i==5 ); /* EACH */
      testcase( i==6 ); /* CHECK */
      testcase( i==7 ); /* KEY */
      testcase( i==8 ); /* BEFORE */
      testcase( i==9 ); /* FOREIGN */
      testcase( i==10 ); /* FOR */
      testcase( i==11 ); /* IGNORE */
      testcase( i==12 ); /* REGEXP */
      testcase( i==13 ); /* EXPLAIN */
      testcase( i==14 ); /* INSTEAD */
      testcase( i==15 ); /* ADD */
      testcase( i==16 ); /* DATABASE */
      testcase( i==17 ); /* AS */
      testcase( i==18 ); /* SELECT */
      testcase( i==19 ); /* TABLE */
      testcase( i==20 ); /* LEFT */
      testcase( i==21 ); /* THEN */
      testcase( i==22 ); /* END */
      testcase( i==23 ); /* DEFERRABLE */
      testcase( i==24 ); /* ELSE */
      testcase( i==25 ); /* EXCEPT */
      testcase( i==26 ); /* TRANSACTION */
      testcase( i==27 ); /* ACTION */
      testcase( i==28 ); /* ON */
      testcase( i==29 ); /* NATURAL */
      testcase( i==30 ); /* ALTER */
      testcase( i==31 ); /* RAISE */
      testcase( i==32 ); /* EXCLUSIVE */
      testcase( i==33 ); /* EXISTS */
      testcase( i==34 ); /* SAVEPOINT */
      testcase( i==35 ); /* INTERSECT */
      testcase( i==36 ); /* TRIGGER */
      testcase( i==37 ); /* REFERENCES */
      testcase( i==38 ); /* CONSTRAINT */
      testcase( i==39 ); /* INTO */
      testcase( i==40 ); /* OFFSET */
      testcase( i==41 ); /* OF */
      testcase( i==42 ); /* SET */
      testcase( i==43 ); /* TEMPORARY */
      testcase( i==44 ); /* TEMP */
      testcase( i==45 ); /* OR */
      testcase( i==46 ); /* UNIQUE */
      testcase( i==47 ); /* QUERY */
      testcase( i==48 ); /* WITHOUT */
      testcase( i==49 ); /* WITH */
      testcase( i==50 ); /* OUTER */
      testcase( i==51 ); /* RELEASE */
      testcase( i==52 ); /* ATTACH */
      testcase( i==53 ); /* HAVING */
      testcase( i==54 ); /* GROUP */
      testcase( i==55 ); /* UPDATE */
      testcase( i==56 ); /* BEGIN */
      testcase( i==57 ); /* INNER */
      testcase( i==58 ); /* RECURSIVE */
      testcase( i==59 ); /* BETWEEN */
      testcase( i==60 ); /* NOTNULL */
      testcase( i==61 ); /* NOT */
      testcase( i==62 ); /* NO */
      testcase( i==63 ); /* NULL */
      testcase( i==64 ); /* LIKE */
      testcase( i==65 ); /* CASCADE */
      testcase( i==66 ); /* ASC */
      testcase( i==67 ); /* DELETE */
      testcase( i==68 ); /* CASE */
      testcase( i==69 ); /* COLLATE */
      testcase( i==70 ); /* CREATE */
      testcase( i==71 ); /* CURRENT_DATE */
      testcase( i==72 ); /* DETACH */
      testcase( i==73 ); /* IMMEDIATE */
      testcase( i==74 ); /* JOIN */
      testcase( i==75 ); /* INSERT */
      testcase( i==76 ); /* MATCH */
      testcase( i==77 ); /* PLAN */
      testcase( i==78 ); /* ANALYZE */
      testcase( i==79 ); /* PRAGMA */
      testcase( i==80 ); /* ABORT */
      testcase( i==81 ); /* VALUES */
      testcase( i==82 ); /* VIRTUAL */
      testcase( i==83 ); /* LIMIT */
      testcase( i==84 ); /* WHEN */
      testcase( i==85 ); /* WHERE */
      testcase( i==86 ); /* RENAME */
      testcase( i==87 ); /* AFTER */
      testcase( i==88 ); /* REPLACE */
      testcase( i==89 ); /* AND */
      testcase( i==90 ); /* DEFAULT */
      testcase( i==91 ); /* AUTOINCREMENT */
      testcase( i==92 ); /* TO */
      testcase( i==93 ); /* IN */
      testcase( i==94 ); /* CAST */
      testcase( i==95 ); /* COLUMN */
      testcase( i==96 ); /* COMMIT */
      testcase( i==97 ); /* CONFLICT */
      testcase( i==98 ); /* CROSS */
      testcase( i==99 ); /* CURRENT_TIMESTAMP */
      testcase( i==100 ); /* CURRENT_TIME */
      testcase( i==101 ); /* PRIMARY */
      testcase( i==102 ); /* DEFERRED */
      testcase( i==103 ); /* DISTINCT */
      testcase( i==104 ); /* IS */
      testcase( i==105 ); /* DROP */
      testcase( i==106 ); /* FAIL */
      testcase( i==107 ); /* FROM */
      testcase( i==108 ); /* FULL */
      testcase( i==109 ); /* GLOB */
      testcase( i==110 ); /* BY */
      testcase( i==111 ); /* IF */
      testcase( i==112 ); /* ISNULL */
      testcase( i==113 ); /* ORDER */
      testcase( i==114 ); /* RESTRICT */
      testcase( i==115 ); /* RIGHT */
      testcase( i==116 ); /* ROLLBACK */
      testcase( i==117 ); /* ROW */
      testcase( i==118 ); /* UNION */
      testcase( i==119 ); /* USING */
      testcase( i==120 ); /* VACUUM */
      testcase( i==121 ); /* VIEW */
      testcase( i==122 ); /* INITIALLY */
      testcase( i==123 ); /* ALL */
      *pType = aKWCode[i];
      break;
    }
  }
  return n;
}