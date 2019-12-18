__attribute__((used)) static void dollar() {
    int $ = 1;
    expect(1, $);
    int $2 = 2;
    expect(2, $2);
    int a$ = 3;
    expect(3, a$);
}